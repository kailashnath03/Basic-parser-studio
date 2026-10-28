const http = require('http');
const app = require('../src/app');

function makeRequest(server, method, path, data = null) {
    return new Promise((resolve, reject) => {
        const addr = server.address();
        const payload = data ? JSON.stringify(data) : null;
        const options = {
            hostname: '127.0.0.1',
            port: addr.port,
            path: path,
            method: method,
            headers: {
                'Content-Type': 'application/json',
                ...(payload ? { 'Content-Length': Buffer.byteLength(payload) } : {})
            }
        };

        const req = http.request(options, (res) => {
            let body = '';
            res.on('data', chunk => body += chunk);
            res.on('end', () => {
                try {
                    const parsed = JSON.parse(body);
                    resolve({ status: res.statusCode, data: parsed });
                } catch (e) {
                    resolve({ status: res.statusCode, raw: body });
                }
            });
        });

        req.on('error', reject);
        if (payload) req.write(payload);
        req.end();
    });
}

async function runTests() {
    console.log('====================================================');
    console.log('       BACKEND API AUTOMATED TEST SUITE             ');
    console.log('====================================================\n');

    let total = 0;
    let passed = 0;
    let failed = 0;

    const server = http.createServer(app);
    await new Promise(resolve => server.listen(0, '127.0.0.1', resolve));

    try {
        // Test 1: Health
        total++;
        const health = await makeRequest(server, 'GET', '/api/health');
        if (health.status === 200 && health.data.status === 'ok' && health.data.parser.available) {
            console.log('  [PASS] GET /api/health -> Parser available and ready');
            passed++;
        } else {
            console.error('  [FAIL] GET /api/health failed:', health);
            failed++;
        }

        // Test 2: Examples
        total++;
        const examplesRes = await makeRequest(server, 'GET', '/api/examples');
        if (examplesRes.status === 200 && examplesRes.data.success && examplesRes.data.examples.length >= 10) {
            console.log(`  [PASS] GET /api/examples -> Loaded ${examplesRes.data.examples.length} examples`);
            passed++;
        } else {
            console.error('  [FAIL] GET /api/examples failed:', examplesRes);
            failed++;
        }

        // Test 3: Parse Valid Code
        total++;
        const validRes = await makeRequest(server, 'POST', '/api/parse', {
            code: 'LET X = 42\nPRINT "X is "; X'
        });
        if (validRes.status === 200 && validRes.data.success === true && validRes.data.status === 'ACCEPTED' && validRes.data.ast) {
            console.log(`  [PASS] POST /api/parse (valid) -> ACCEPTED (${validRes.data.tokens.length} tokens, ${validRes.data.executionTimeMs}ms)`);
            passed++;
        } else {
            console.error('  [FAIL] POST /api/parse (valid) failed:', validRes);
            failed++;
        }

        // Test 4: Parse Invalid Code
        total++;
        const invalidRes = await makeRequest(server, 'POST', '/api/parse', {
            code: 'LET X = 2 + * 4'
        });
        if (invalidRes.status === 200 && invalidRes.data.success === false && invalidRes.data.status === 'REJECTED' && invalidRes.data.diagnostics.length > 0) {
            console.log(`  [PASS] POST /api/parse (syntax error) -> REJECTED correctly with ${invalidRes.data.diagnostics.length} diagnostic(s)`);
            passed++;
        } else {
            console.error('  [FAIL] POST /api/parse (syntax error) failed:', invalidRes);
            failed++;
        }

        // Test 5: Missing body validation
        total++;
        const missingBodyRes = await makeRequest(server, 'POST', '/api/parse', {});
        if (missingBodyRes.status === 400 && missingBodyRes.data.error) {
            console.log('  [PASS] POST /api/parse (missing code) -> 400 Bad Request');
            passed++;
        } else {
            console.error('  [FAIL] POST /api/parse (missing code) failed:', missingBodyRes);
            failed++;
        }

        // Test 6: Verify all examples against the real parser
        console.log('\n--- Verifying All Examples Through API ---');
        for (const ex of examplesRes.data.examples) {
            total++;
            const parseEx = await makeRequest(server, 'POST', '/api/parse', { code: ex.code });
            const matchesExpected = parseEx.data.status === ex.expectedStatus;
            if (matchesExpected) {
                console.log(`  [PASS] Example "${ex.name}" matches expected status: ${ex.expectedStatus}`);
                passed++;
            } else {
                console.error(`  [FAIL] Example "${ex.name}" expected ${ex.expectedStatus} but got ${parseEx.data.status}`);
                failed++;
            }
        }

    } finally {
        server.close();
    }

    console.log('\n====================================================');
    console.log(`API Tests: ${passed}/${total} Passed (${failed} Failed)`);
    console.log('====================================================');

    if (failed > 0) {
        process.exit(1);
    }
}

runTests().catch(err => {
    console.error('Fatal test error:', err);
    process.exit(1);
});

