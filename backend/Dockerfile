# Production Dockerfile for Render Web Service Deployment
# Context: Repository root (.)

FROM node:20-bookworm-slim AS production

# Install compiler tools: Flex, GNU Bison, GCC, Make, libc-dev
RUN apt-get update && apt-get install -y --no-install-recommends \
    flex \
    bison \
    gcc \
    make \
    libc6-dev \
 && rm -rf /var/lib/apt/lists/*

# Set container working directory
WORKDIR /app

# Copy backend package manifests first for efficient Docker layer caching
COPY backend/package*.json ./backend/

# Install production dependencies for the Express backend
WORKDIR /app/backend
RUN npm ci --omit=dev || npm install --production

# Switch to root to copy parser and backend sources
WORKDIR /app
COPY parser/ ./parser/
COPY backend/ ./backend/

# Build the C Flex & Bison BASIC parser binary natively
WORKDIR /app/parser
# Remove any accidental Windows binaries or pre-generated files
RUN rm -f basic_parser.exe basic_parser parser.tab.* lex.yy.* *.o 2>/dev/null || true
RUN make all
RUN chmod +x basic_parser && ls -la basic_parser

# Run the automated parser test suite during Docker build to verify compiler integrity
RUN node run_tests.js

# Return to backend directory
WORKDIR /app/backend

# Render deployment environment variables
ENV NODE_ENV=production
ENV PORT=10000
ENV PARSER_BIN_PATH=/app/parser/basic_parser

# Expose Render default port
EXPOSE 10000

# Start Express server
CMD ["node", "src/server.js"]

