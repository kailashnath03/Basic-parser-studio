require('dotenv').config();
const app = require('./app');
const parserService = require('./services/parser.service');

const PORT = process.env.PORT || 10000;
const HOST = '0.0.0.0';

const server = app.listen(PORT, HOST, () => {
    console.log(`====================================================`);
    console.log(`  BASIC Parser Studio API Server`);
    console.log(`  Listening on: http://${HOST}:${PORT}`);
    console.log(`  Health Check: http://${HOST}:${PORT}/api/health`);
    console.log(`  Examples:     http://${HOST}:${PORT}/api/examples`);
    console.log(`  Parser Path:  ${parserService.parserPath}`);
    console.log(`  Parser Ready: ${parserService.isParserAvailable() ? 'YES' : 'NO'}`);
    console.log(`  Environment:  ${process.env.NODE_ENV || 'development'}`);
    console.log(`====================================================`);
});

module.exports = server;
