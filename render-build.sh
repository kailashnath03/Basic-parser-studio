#!/usr/bin/env bash
set -euo pipefail

echo "===================================================="
echo "  BASIC Parser Studio: Native Render Build Script   "
echo "===================================================="

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PARSER_DIR="$REPO_ROOT/parser"
BACKEND_DIR="$REPO_ROOT/backend"

echo "[1/4] Checking GCC compiler..."
if ! command -v gcc >/dev/null 2>&1; then
    echo "ERROR: gcc is required but not found in PATH." >&2
    exit 1
fi
echo "  - GCC: $(gcc --version | head -n 1)"

echo "[2/4] Verifying C parser source files..."
# If Bison / Flex are available and files need updating, re-run them; otherwise use committed C sources
if [ ! -f "$PARSER_DIR/parser.tab.c" ] || [ ! -f "$PARSER_DIR/parser.tab.h" ]; then
    if command -v bison >/dev/null 2>&1; then
        echo "  -> Running bison to generate parser.tab.c..."
        bison -d -Wall -o "$PARSER_DIR/parser.tab.c" "$PARSER_DIR/parser.y"
    else
        echo "ERROR: parser.tab.c missing and bison not installed." >&2
        exit 1
    fi
fi

if [ ! -f "$PARSER_DIR/lex.yy.c" ]; then
    if command -v flex >/dev/null 2>&1; then
        echo "  -> Running flex to generate lex.yy.c..."
        flex -o "$PARSER_DIR/lex.yy.c" "$PARSER_DIR/lexer.l"
    else
        echo "ERROR: lex.yy.c missing and flex not installed." >&2
        exit 1
    fi
fi
echo "  ✓ C parser files ready: parser.tab.c, parser.tab.h, lex.yy.c"

echo "[3/4] Compiling native parser executable (basic_parser)..."
cd "$PARSER_DIR"
rm -f basic_parser
gcc -Wall -Wextra -std=c11 -O2 -D_POSIX_C_SOURCE=200809L -D_GNU_SOURCE -o basic_parser main.c ast.c parser.tab.c lex.yy.c
chmod +x basic_parser

if [ ! -x basic_parser ]; then
    echo "ERROR: Compiled parser executable not found or not executable!" >&2
    exit 1
fi
echo "  ✓ Compiled parser binary successfully at $PARSER_DIR/basic_parser"

# Run tests
echo "  -> Running parser tests..."
node run_tests.js

echo "[4/4] Installing backend dependencies..."
cd "$BACKEND_DIR"
npm install --production

echo "===================================================="
echo "  Render Build Succeeded! Ready for start.          "
echo "===================================================="
