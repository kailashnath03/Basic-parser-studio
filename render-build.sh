#!/usr/bin/env bash
set -euo pipefail

echo "===================================================="
echo "  BASIC Parser Studio: Native Render Build Script   "
echo "===================================================="

# Determine repo directories
REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PARSER_DIR="$REPO_ROOT/parser"
BACKEND_DIR="$REPO_ROOT/backend"
TOOLS_DIR="$REPO_ROOT/.render-tools"

echo "[1/5] Checking compiler toolchain (GCC, Flex, Bison)..."

if ! command -v gcc >/dev/null 2>&1; then
    echo "ERROR: gcc is required but not found in PATH." >&2
    exit 1
fi

# Add local tools directory to PATH in case they were installed in a previous step or cache
export PATH="$TOOLS_DIR/opt/usr/bin:$TOOLS_DIR/opt/bin:$PATH"
if [ -d "$TOOLS_DIR/opt/usr/share/bison" ]; then
    export BISON_PKGDATADIR="$TOOLS_DIR/opt/usr/share/bison"
fi
if [ -d "$TOOLS_DIR/opt/usr/lib/x86_64-linux-gnu" ]; then
    export LD_LIBRARY_PATH="$TOOLS_DIR/opt/usr/lib/x86_64-linux-gnu:${LD_LIBRARY_PATH:-}"
fi

check_tool() {
    local cmd="$1"
    command -v "$cmd" >/dev/null 2>&1
}

if ! check_tool bison || ! check_tool flex; then
    echo "  -> System is missing bison or flex. Installing in user-space ($TOOLS_DIR)..."
    mkdir -p "$TOOLS_DIR/deb" "$TOOLS_DIR/opt"
    cd "$TOOLS_DIR/deb"

    # Attempt 1: apt-get download (runs as normal unprivileged user)
    echo "  -> Trying 'apt-get download'..."
    if apt-get download bison flex libfl2 libbison-dev m4 2>/dev/null; then
        echo "  -> Successfully fetched deb packages via apt-get download."
    else
        echo "  -> apt-get download unavailable; downloading deb packages directly via curl..."
        DEB_PACKAGES=(
            "http://ftp.debian.org/debian/pool/main/b/bison/bison_3.8.2+dfsg-1+b1_amd64.deb"
            "http://ftp.debian.org/debian/pool/main/b/bison/libbison-dev_3.8.2+dfsg-1+b1_amd64.deb"
            "http://ftp.debian.org/debian/pool/main/f/flex/flex_2.6.4-8.2_amd64.deb"
            "http://ftp.debian.org/debian/pool/main/f/flex/libfl2_2.6.4-8.2_amd64.deb"
            "http://ftp.debian.org/debian/pool/main/m/m4/m4_1.4.19-3_amd64.deb"
        )
        for url in "${DEB_PACKAGES[@]}"; do
            fname="$(basename "$url")"
            if [ ! -f "$fname" ]; then
                echo "     Downloading $fname..."
                curl -sSL -f -o "$fname" "$url" || echo "     Warning: could not download $fname"
            fi
        done
    fi

    # Extract all .deb archives into $TOOLS_DIR/opt
    echo "  -> Extracting packages to $TOOLS_DIR/opt..."
    for deb in *.deb; do
        if [ -f "$deb" ]; then
            if command -v dpkg-deb >/dev/null 2>&1; then
                dpkg-deb -x "$deb" "$TOOLS_DIR/opt"
            elif command -v dpkg >/dev/null 2>&1; then
                dpkg -x "$deb" "$TOOLS_DIR/opt"
            else
                ar -x "$deb" 2>/dev/null || true
                if [ -f data.tar.xz ]; then
                    tar -xf data.tar.xz -C "$TOOLS_DIR/opt"
                    rm -f data.tar.xz
                elif [ -f data.tar.gz ]; then
                    tar -xf data.tar.gz -C "$TOOLS_DIR/opt"
                    rm -f data.tar.gz
                fi
                rm -f control.tar.* debian-binary
            fi
        fi
    done

    export PATH="$TOOLS_DIR/opt/usr/bin:$TOOLS_DIR/opt/bin:$PATH"
    export BISON_PKGDATADIR="$TOOLS_DIR/opt/usr/share/bison"
    if [ -d "$TOOLS_DIR/opt/usr/lib/x86_64-linux-gnu" ]; then
        export LD_LIBRARY_PATH="$TOOLS_DIR/opt/usr/lib/x86_64-linux-gnu:${LD_LIBRARY_PATH:-}"
    fi

    cd "$REPO_ROOT"
fi

echo "  - GCC:   $(gcc --version | head -n 1)"
echo "  - Bison: $(bison --version | head -n 1)"
echo "  - Flex:  $(flex --version | head -n 1)"

echo "[2/5] Running Bison and Flex to generate C source files..."
cd "$PARSER_DIR"

# Clean any existing generated files
rm -f parser.tab.c parser.tab.h lex.yy.c parser.output basic_parser

# Generate parser with Bison
echo "  -> Executing: bison -d -Wall -o parser.tab.c parser.y"
bison -d -Wall -o parser.tab.c parser.y

# Generate lexer with Flex
echo "  -> Executing: flex -o lex.yy.c lexer.l"
flex -o lex.yy.c lexer.l

if [ ! -f parser.tab.c ] || [ ! -f parser.tab.h ]; then
    echo "ERROR: Bison failed to generate parser.tab.c or parser.tab.h" >&2
    exit 1
fi

if [ ! -f lex.yy.c ]; then
    echo "ERROR: Flex failed to generate lex.yy.c" >&2
    exit 1
fi
echo "  ✓ Generated files verified: parser.tab.c, parser.tab.h, lex.yy.c"

echo "[3/5] Compiling parser binary (basic_parser)..."
gcc -Wall -Wextra -std=c11 -O2 -o basic_parser main.c ast.c parser.tab.c lex.yy.c
chmod +x basic_parser

if [ ! -x basic_parser ]; then
    echo "ERROR: Compiled parser executable not found or not executable!" >&2
    exit 1
fi
echo "  ✓ Compiled parser binary successfully at $PARSER_DIR/basic_parser"

echo "[4/5] Running parser automated tests..."
node run_tests.js

echo "[5/5] Installing backend dependencies..."
cd "$BACKEND_DIR"
npm install --production

echo "===================================================="
echo "  Render Native Build Succeeded! Ready for start.    "
echo "===================================================="
