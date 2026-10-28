const express = require('express');
const router = express.Router();
const parserService = require('../services/parser.service');
const examples = require('../examples');

// GET /api/health
router.get('/health', (req, res) => {
    const parserInfo = parserService.getParserInfo();
    res.json({
        status: 'ok',
        service: 'BASIC Parser Studio API',
        uptime: process.uptime(),
        timestamp: new Date().toISOString(),
        parser: parserInfo
    });
});

// GET /api/examples
router.get('/examples', (req, res) => {
    res.json({
        success: true,
        count: examples.length,
        examples
    });
});

// POST /api/parse
router.post('/parse', async (req, res) => {
    const { code } = req.body;

    if (code === undefined || code === null) {
        return res.status(400).json({
            success: false,
            error: 'Missing required field: "code"'
        });
    }

    if (typeof code !== 'string') {
        return res.status(400).json({
            success: false,
            error: 'Field "code" must be a string'
        });
    }

    try {
        const result = await parserService.parseCode(code);
        return res.json(result);
    } catch (err) {
        console.error('Parse error:', err);
        return res.status(500).json({
            success: false,
            status: 'ERROR',
            error: err.message,
            tokens: [],
            ast: null,
            diagnostics: [{
                type: 'INTERNAL_ERROR',
                message: err.message,
                line: 1,
                column: 1,
                snippet: ''
            }],
            statistics: {
                tokenCount: 0,
                errorCount: 1,
                lineCount: 0,
                parseStatus: 'ERROR'
            }
        });
    }
});

module.exports = router;

