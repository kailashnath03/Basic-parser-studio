const express = require('express');
const cors = require('cors');
const parserRoutes = require('./routes/parser.routes');

const app = express();

// Configure CORS
const isProduction = process.env.NODE_ENV === 'production';
const rawFrontendUrls = process.env.FRONTEND_URL || '';
const allowedOrigins = rawFrontendUrls
    .split(',')
    .map(url => url.trim().replace(/\/+$/, ''))
    .filter(Boolean);

const corsOptions = {
    origin: (origin, callback) => {
        // Allow requests with no origin (e.g. server-to-server, curl, Render health checks, Postman)
        if (!origin) return callback(null, true);

        const normalizedOrigin = origin.replace(/\/+$/, '');

        // If FRONTEND_URL is explicitly set, check if the origin matches
        if (allowedOrigins.length > 0) {
            if (allowedOrigins.includes(normalizedOrigin) || allowedOrigins.includes('*')) {
                return callback(null, true);
            }
        }

        // In non-production environments, allow local development ports
        if (!isProduction) {
            if (
                allowedOrigins.length === 0 ||
                normalizedOrigin.startsWith('http://localhost:') ||
                normalizedOrigin.startsWith('http://127.0.0.1:')
            ) {
                return callback(null, true);
            }
        }

        return callback(new Error(`CORS policy rejection: Origin '${origin}' is not authorized.`));
    },
    credentials: true,
    methods: ['GET', 'POST', 'OPTIONS'],
    allowedHeaders: ['Content-Type', 'Authorization', 'Accept']
};

app.use(cors(corsOptions));
app.use(express.json({ limit: '1mb' }));
app.use(express.urlencoded({ extended: true, limit: '1mb' }));

// API Routes
app.use('/api', parserRoutes);

// Root greeting
app.get('/', (req, res) => {
    res.json({
        service: 'BASIC Parser Studio Backend API',
        status: 'online',
        endpoints: [
            'GET /api/health',
            'GET /api/examples',
            'POST /api/parse'
        ]
    });
});

// 404 handler
app.use((req, res) => {
    res.status(404).json({
        error: 'Not Found',
        message: `Endpoint ${req.method} ${req.url} does not exist.`
    });
});

// Global Error handler
app.use((err, req, res, next) => {
    if (err.message && err.message.includes('CORS policy rejection')) {
        return res.status(403).json({
            error: 'Forbidden',
            message: err.message
        });
    }
    console.error('Unhandled server error:', err);
    res.status(500).json({
        error: 'Internal Server Error',
        message: err.message
    });
});

module.exports = app;
