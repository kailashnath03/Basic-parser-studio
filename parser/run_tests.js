const fs = require('fs');
const path = require('path');
const { spawnSync } = require('child_process');

const parserDir = __dirname;
const isWindows = process.platform === 'win32';
const parserExecutable = path.join(parserDir, isWindows ? 'basic_parser.exe' : 'basic_parser');

if (!fs.existsSync(parserExecutable)) {
    console.error(`Error: Parser executable not found at: ${parserExecutable}`);
    console.error('Please build the parser first using make.');
    process.exit(1);
}

const validDir = path.join(parserDir, 'tests', 'valid');
const invalidDir = path.join(parserDir, 'tests', 'invalid');

let totalTests = 0;
let passedTests = 0;
let failedTests = 0;

console.log('====================================================');
console.log('       BASIC PARSER AUTOMATED TEST SUITE            ');
console.log('====================================================\n');

// 1. Valid tests
console.log('--- Testing Valid BASIC Programs (Expected: ACCEPTED) ---');
const validFiles = fs.readdirSync(validDir).filter(f => f.endsWith('.bas')).sort();

for (const file of validFiles) {
    totalTests++;
    const filePath = path.join(validDir, file);
    const content = fs.readFileSync(filePath, 'utf-8');

    const result = spawnSync(parserExecutable, ['--json', filePath], {
        encoding: 'utf-8',
        timeout: 5000
    });

    try {
        const json = JSON.parse(result.stdout);
        if (result.status === 0 && json.success === true && json.status === 'ACCEPTED' && json.ast !== null) {
            console.log(`  [PASS] ${file} -> Tokens: ${json.statistics.tokenCount}, Errors: 0`);
            passedTests++;
        } else {
            console.error(`  [FAIL] ${file} -> Expected ACCEPTED, got status ${json.status}, errors: ${JSON.stringify(json.diagnostics)}`);
            failedTests++;
        }
    } catch (e) {
        console.error(`  [FAIL] ${file} -> Invalid JSON output: ${e.message}\nOutput: ${result.stdout}\nStderr: ${result.stderr}`);
        failedTests++;
    }
}

// 2. Invalid tests
console.log('\n--- Testing Invalid BASIC Programs (Expected: REJECTED) ---');
const invalidFiles = fs.readdirSync(invalidDir).filter(f => f.endsWith('.bas')).sort();

for (const file of invalidFiles) {
    totalTests++;
    const filePath = path.join(invalidDir, file);

    const result = spawnSync(parserExecutable, ['--json', filePath], {
        encoding: 'utf-8',
        timeout: 5000
    });

    try {
        const json = JSON.parse(result.stdout);
        if (result.status !== 0 && json.success === false && json.status === 'REJECTED' && json.statistics.errorCount > 0) {
            console.log(`  [PASS] ${file} -> Caught ${json.statistics.errorCount} error(s): "${json.diagnostics[0]?.message}"`);
            passedTests++;
        } else {
            console.error(`  [FAIL] ${file} -> Expected REJECTED, but got success=${json.success}, status=${json.status}`);
            failedTests++;
        }
    } catch (e) {
        console.error(`  [FAIL] ${file} -> Invalid JSON output: ${e.message}\nOutput: ${result.stdout}`);
        failedTests++;
    }
}

console.log('\n====================================================');
console.log(`Results: ${passedTests}/${totalTests} Passed (${failedTests} Failed)`);
console.log('====================================================');

if (failedTests > 0) {
    process.exit(1);
}

