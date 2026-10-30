const { spawn } = require('child_process');
const fs = require('fs');
const path = require('path');

class ParserService {
    constructor() {
        this.parserPath = this.resolveParserPath();
    }

    resolveParserPath() {
        const envPath = process.env.PARSER_BIN_PATH;
        if (envPath) {
            const resolved = path.resolve(process.cwd(), envPath);
            if (fs.existsSync(resolved)) return resolved;
        }

        const isWindows = process.platform === 'win32';
        const binName = isWindows ? 'basic_parser.exe' : 'basic_parser';

        // Candidates to search
        const candidates = [
            path.join(__dirname, '..', '..', '..', 'parser', binName),
            path.join(__dirname, '..', '..', 'parser', binName),
            path.join(process.cwd(), 'parser', binName),
            path.join(process.cwd(), '..', 'parser', binName),
            path.join('/app', 'parser', binName),
            path.join('/usr/local/bin', binName)
        ];

        for (const candidate of candidates) {
            if (fs.existsSync(candidate)) {
                return candidate;
            }
        }

        return path.join(__dirname, '..', '..', '..', 'parser', binName);
    }

    isParserAvailable() {
        if (!fs.existsSync(this.parserPath)) {
            this.parserPath = this.resolveParserPath();
        }
        return fs.existsSync(this.parserPath);
    }

    getParserInfo() {
        const available = this.isParserAvailable();
        return {
            path: this.parserPath,
            available: available,
            platform: process.platform
        };
    }

    async parseCode(code) {
        if (!this.isParserAvailable()) {
            throw new Error(`Parser executable not found at: ${this.parserPath}. Please run 'make' inside the parser directory.`);
        }

        if (typeof code !== 'string') {
            throw new Error('Invalid input: "code" field must be a string.');
        }

        const MAX_SIZE_BYTES = 500 * 1024; // 500 KB limit
        if (Buffer.byteLength(code, 'utf8') > MAX_SIZE_BYTES) {
            throw new Error('Source code exceeds maximum allowed size (500 KB).');
        }

        const startTime = Date.now();

        return new Promise((resolve, reject) => {
            const child = spawn(this.parserPath, ['--json'], {
                timeout: 5000,
                stdio: ['pipe', 'pipe', 'pipe']
            });

            let stdout = '';
            let stderr = '';

            child.stdout.on('data', (chunk) => {
                stdout += chunk;
            });

            child.stderr.on('data', (chunk) => {
                stderr += chunk;
            });

            child.on('error', (err) => {
                reject(new Error(`Failed to execute parser process: ${err.message}`));
            });

            child.stdin.on('error', (err) => {
                if (err.code !== 'EPIPE') {
                    console.error('Child stdin error:', err);
                }
            });

            child.on('close', (code, signal) => {
                const executionTimeMs = Date.now() - startTime;

                if (signal === 'SIGTERM' || signal === 'SIGKILL') {
                    return resolve({
                        success: false,
                        status: 'TIMEOUT',
                        tokens: [],
                        ast: null,
                        diagnostics: [{
                            type: 'TIMEOUT_ERROR',
                            message: 'Parsing timed out after 5000ms.',
                            line: 1,
                            column: 1,
                            snippet: ''
                        }],
                        statistics: {
                            tokenCount: 0,
                            errorCount: 1,
                            lineCount: 0,
                            parseStatus: 'TIMEOUT'
                        },
                        executionTimeMs
                    });
                }

                try {
                    const parsed = JSON.parse(stdout);
                    parsed.executionTimeMs = executionTimeMs;
                    resolve(parsed);
                } catch (jsonErr) {
                    // Parser output could not be parsed as JSON
                    const crashDetail = signal ? `Process killed by signal ${signal}` : (code !== 0 ? `Process exited with code ${code}` : jsonErr.message);
                    resolve({
                        success: false,
                        status: 'INTERNAL_ERROR',
                        tokens: [],
                        ast: null,
                        diagnostics: [{
                            type: 'PARSER_CRASH',
                            message: `Internal parser error: ${stderr ? stderr.trim() : crashDetail}`,
                            line: 1,
                            column: 1,
                            snippet: stdout.slice(0, 200)
                        }],
                        statistics: {
                            tokenCount: 0,
                            errorCount: 1,
                            lineCount: 0,
                            parseStatus: 'INTERNAL_ERROR'
                        },
                        executionTimeMs
                    });
                }
            });

            // Feed code to parser stdin safely
            try {
                child.stdin.write(code);
                child.stdin.end();
            } catch (stdinErr) {
                reject(new Error(`Error writing to parser stdin: ${stdinErr.message}`));
            }
        });
    }
}

module.exports = new ParserService();

