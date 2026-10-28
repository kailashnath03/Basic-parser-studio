# BASIC Parser Studio 🚀

**A Full-Stack Compiler Design Laboratory Project: Building a Lexical & Syntax Analyzer for BASIC using Flex, GNU Bison (Yacc), C, Express.js, and React.**

---

> **IMPORTANT NOTICE:**  
> This application is an educational **Syntax and Lexical Analyzer** for a well-defined subset of traditional, Dartmouth / QBASIC-style BASIC. It generates tokens, validates Context-Free Grammar (CFG) production rules, reports syntax and lexical diagnostics with exact line and column numbers, and constructs an **Abstract Syntax Tree (AST)**.  
> **It is NOT an interpreter or runtime engine and does NOT execute submitted BASIC programs.**

---

## 📑 Table of Contents

1. [Project Overview](#project-overview)
2. [What is the BASIC Language?](#what-is-the-basic-language)
3. [Compiler Design Fundamentals](#compiler-design-fundamentals)
   - [Lexical Analysis (Flex)](#1-lexical-analysis-flex)
   - [Syntax Analysis (GNU Bison / Yacc)](#2-syntax-analysis-gnu-bison--yacc)
   - [Abstract Syntax Tree (AST) Construction](#3-abstract-syntax-tree-ast-construction)
4. [System Architecture](#system-architecture)
5. [Supported BASIC Language Dialect](#supported-basic-language-dialect)
   - [Grammar Production Rules (BNF)](#grammar-production-rules-bnf)
   - [Operator Precedence & Associativity Hierarchy](#operator-precedence--associativity-hierarchy)
   - [Lexical Token Specifications](#lexical-token-specifications)
6. [Project Directory Structure](#project-directory-structure)
7. [Prerequisites & Environment Setup](#prerequisites--environment-setup)
   - [Windows Setup (MinGW & WinFlexBison)](#windows-native)
   - [Ubuntu / WSL Setup](#ubuntu--linux--wsl)
8. [Build and Execution Guide](#build-and-execution-guide)
   - [1. Compile the Parser Engine](#1-compile-the-parser-engine)
   - [2. Start the Backend API](#2-start-the-backend-api)
   - [3. Start the Frontend Studio](#3-start-the-frontend-studio)
9. [Automated Testing Suite](#automated-testing-suite)
10. [Sample Programs (Valid & Invalid)](#sample-programs)
11. [College Lab Presentation Demonstration Workflow](#college-lab-presentation-demonstration-workflow)
12. [Troubleshooting & FAQs](#troubleshooting--faqs)

---

## 1. Project Overview

**BASIC Parser Studio** is a developer tool and interactive educational studio built to demonstrate the initial phases of compiler construction for a programming language.

The application allows students, professors, and software engineers to:
1. Write or paste BASIC source code into a code editor.
2. Trigger syntax and lexical analysis by invoking a real compiled Flex/Bison C binary.
3. Inspect the stream of tokens produced by the **Flex** lexical analyzer (with type, lexeme, line, and column coordinates).
4. Verify whether the **GNU Bison** LALR(1) parser accepts or rejects the program against defined context-free grammar rules.
5. Explore the hierarchical **Abstract Syntax Tree (AST)** interactively with node inspection and raw JSON export.
6. View informative diagnostics for syntax and lexical errors, complete with source snippets and caret pointers.
7. Study context-free grammar production rules, token definitions, and operator precedence tables.

---

## 2. What is the BASIC Language?

**BASIC** (*Beginner's All-purpose Symbolic Instruction Code*) was originally designed in 1964 by John G. Kemeny and Thomas E. Kurtz at Dartmouth College to provide accessible computing for non-technical students. It evolved through dialects such as Microsoft GW-BASIC, QuickBASIC, and QBASIC.

### Key Characteristics:
- **Line-oriented syntax:** Statements separated by newlines or colons (`:`).
- **Optional line numbers:** Traditional numeric line numbers (e.g., `10 PRINT "HI"`, `20 GOTO 10`).
- **Dynamic typing with type suffixes:** Variables do not require prior declaration; string variables end with `$` (e.g. `NAME$`).
- **Human-readable control flow:** `IF ... THEN ... ELSE ... END IF`, `FOR ... TO ... STEP ... NEXT`, `WHILE ... WEND`.

### Real-World Applications:
- Historical bedrock of microcomputers (Commodore 64, Apple II, IBM PC).
- Embedded automation scripts and macro engines (VBA in Microsoft Excel, Visual Basic).
- Industrial automation and PLCs (e.g. Omron, Keyence BASIC-like scripting).
- Foundational dialect for learning compiler design and language parsing theory.

---

## 3. Compiler Design Fundamentals

A compiler traditionally consists of a front-end (analysis) and a back-end (synthesis):

```text
Source Code (.bas)
       │
       ▼
┌─────────────────────────┐
│   Lexical Analysis      │  ===> Flex (lexer.l) -> Token Stream
└─────────────────────────┘
       │
       ▼
┌─────────────────────────┐
│   Syntax Analysis       │  ===> GNU Bison (parser.y) -> LALR(1) Parsing
└─────────────────────────┘
       │
       ▼
┌─────────────────────────┐
│ Abstract Syntax Tree    │  ===> C Data Structures (ast.c / ast.h)
└─────────────────────────┘
       │
       ▼
┌─────────────────────────┐
│ JSON Output Protocol    │  ===> Standardized Output to REST API & UI
└─────────────────────────┘
```

### 1. Lexical Analysis (Flex)
- **Role:** Converts a stream of characters into a stream of meaningful tokens.
- **Specification:** [`parser/lexer.l`](parser/lexer.l)
- **Features:**
  - Case-insensitive keyword matching (`PRINT`, `print`, `Print`).
  - Distinguishes statement boundaries (`\n` as `TOKEN_EOL`, `:` as `TOKEN_COLON`) from whitespace.
  - Matches longer operators first (`<=`, `>=`, `<>`) before single-character prefixes.
  - Correctly avoids treating `REM` inside an identifier (e.g., `REMARK = 10`) as a comment.
  - Tracks 1-indexed line and column numbers.

### 2. Syntax Analysis (GNU Bison / Yacc)
- **Role:** Verifies whether the stream of tokens conforms to the Context-Free Grammar (CFG) rules of the BASIC language.
- **Specification:** [`parser/parser.y`](parser/parser.y)
- **Features:**
  - LALR(1) bottom-up shift-reduce parser.
  - **Zero shift/reduce and zero reduce/reduce conflicts** achieved through explicit statement boundary separation and operator precedence declarations.
  - Handles multiline blocks (`IF ... END IF`, `FOR ... NEXT`, `WHILE ... WEND`) and single-line constructs (`IF ... THEN ... ELSE`).

### 3. Abstract Syntax Tree (AST) Construction
- **Role:** Constructs a syntax tree that captures the hierarchical structure of expressions and statements while discarding syntactic noise (semicolons, parentheses).
- **Specification:** [`parser/ast.h`](parser/ast.h), [`parser/ast.c`](parser/ast.c)
- **Features:**
  - Recursive C node structures with source locations.
  - Correct operator precedence (e.g. `2 + 3 * 4` places `*` as child of `+`).
  - JSON serialization with RFC-compliant string escaping.

---

## 4. System Architecture

```text
┌─────────────────────────────────────────────────────────────┐
│                    REACT VITE FRONTEND                      │
│   • Monaco Editor     • Custom React Interactive AST Tree   │
│   • Token Table       • Diagnostic Snippet Previews         │
│   • Grammar Reference • Example Programs Dropdown           │
└──────────────────────────────┬──────────────────────────────┘
                               │ HTTP / JSON
                               ▼
┌─────────────────────────────────────────────────────────────┐
│                    EXPRESS.JS BACKEND                       │
│   • GET  /api/health       -> Check parser binary status    │
│   • GET  /api/examples     -> 13 verified sample programs   │
│   • POST /api/parse        -> Safe child_process.spawn()    │
└──────────────────────────────┬──────────────────────────────┘
                               │ Stdin / Stdout (JSON Protocol)
                               ▼
┌─────────────────────────────────────────────────────────────┐
│                NATIVE COMPILED PARSER (C)                   │
│   • Flex Lexer (lexer.yy.c) • Bison Parser (parser.tab.c)   │
│   • AST Engine (ast.c)      • Output Serializer (main.c)    │
└─────────────────────────────────────────────────────────────┘
```

---

## 5. Supported BASIC Language Dialect

### Grammar Production Rules (BNF)

```text
program             ::= lines

lines               ::= ε
                      | lines line

line                ::= EOL
                      | [ line_label ] statements_on_line EOL

line_label          ::= INT_LITERAL

statements_on_line  ::= statement
                      | statements_on_line ':' statement

statement           ::= assignment_stmt
                      | print_stmt
                      | input_stmt
                      | if_stmt
                      | for_stmt
                      | while_stmt
                      | goto_stmt
                      | gosub_stmt
                      | return_stmt
                      | end_stmt
                      | stop_stmt

assignment_stmt     ::= [ LET ] IDENTIFIER '=' expression

print_stmt          ::= PRINT [ print_item_list ] [ ',' | ';' ]

print_item_list     ::= print_item
                      | print_item_list ( ',' | ';' ) print_item

print_item          ::= expression

input_stmt          ::= INPUT var_list
                      | INPUT STRING_LITERAL ( ';' | ',' ) var_list

var_list            ::= IDENTIFIER
                      | var_list ',' IDENTIFIER

if_stmt             ::= IF expression THEN EOL block_lines [ else_clause ] END IF
                      | IF expression THEN statement [ ELSE statement ]

else_clause         ::= ELSE EOL block_lines
                      | ELSEIF expression THEN EOL block_lines [ else_clause ]

for_stmt            ::= FOR IDENTIFIER '=' expression TO expression [ STEP expression ] EOL
                            block_lines
                        NEXT [ IDENTIFIER ]

while_stmt          ::= WHILE expression EOL
                            block_lines
                        WEND

goto_stmt           ::= GOTO ( INT_LITERAL | IDENTIFIER )
gosub_stmt          ::= GOSUB ( INT_LITERAL | IDENTIFIER )
return_stmt         ::= RETURN
end_stmt            ::= END
stop_stmt           ::= STOP
```

### Operator Precedence & Associativity Hierarchy

| Precedence | Operator | Operation | Associativity |
|---|---|---|---|
| **1 (Highest)** | `^` | Exponentiation | Right-to-Left |
| **2** | `+`, `-` (unary) | Unary Sign | Right-to-Left |
| **3** | `*`, `/`, `\`, `MOD` | Multiplication, Division, Modulo | Left-to-Right |
| **4** | `+`, `-` | Addition, Subtraction | Left-to-Right |
| **5** | `=`, `<>`, `<`, `>`, `<=`, `>=` | Relational Comparisons | Non-associative |
| **6** | `NOT` | Logical Negation | Right-to-Left |
| **7** | `AND` | Logical Conjunction | Left-to-Right |
| **8 (Lowest)** | `OR` | Logical Disjunction | Left-to-Right |

---

## 6. Project Directory Structure

```text
BASIC LANGUAGE/
├── parser/
│   ├── lexer.l             # Flex lexical analyzer specification
│   ├── parser.y            # GNU Bison LALR(1) context-free grammar
│   ├── ast.h               # Abstract Syntax Tree node definitions
│   ├── ast.c               # AST construction & JSON serialization
│   ├── main.c              # Parser CLI driver & protocol handler
│   ├── Makefile            # Build automation for GCC, Flex, Bison
│   ├── run_tests.js        # Automated test suite runner (21 tests)
│   └── tests/
│       ├── valid/          # 12 valid BASIC programs
│       └── invalid/        # 9 invalid BASIC programs
├── backend/
│   ├── package.json        # Express, Cors, Dotenv
│   ├── .env.example        # Environment variable template
│   ├── src/
│   │   ├── app.js          # Express app configuration & middleware
│   │   ├── server.js       # HTTP server launcher
│   │   ├── examples.js     # 13 verified sample programs
│   │   ├── routes/
│   │   │   └── parser.routes.js  # /health, /examples, /parse
│   │   └── services/
│   │       └── parser.service.js # Child process execution & timeouts
│   └── test/
│       └── api.test.js     # Automated API test suite (18 tests)
├── frontend/
│   ├── package.json        # React, Vite, Bootstrap, Monaco, Lucide
│   ├── vite.config.js      # Vite configuration & backend proxy
│   ├── index.html          # HTML entry point
│   └── src/
│       ├── components/
│       │   ├── Navbar.jsx         # Navigation bar & health badge
│       │   ├── EditorPanel.jsx    # Code editor & toolbar
│       │   ├── StatsBanner.jsx    # Status chip & statistics metrics
│       │   ├── TokensTab.jsx      # Token data table & filtering
│       │   ├── AstViewer.jsx      # Interactive collapsible AST tree
│       │   ├── DiagnosticsTab.jsx # Diagnostic error cards & pointers
│       │   ├── GrammarTab.jsx     # Context-Free Grammar documentation
│       │   └── AboutModal.jsx     # Compiler architecture & lab details
│       ├── services/
│       │   └── api.js             # Frontend API client
│       ├── App.jsx                # Main workbench orchestrator
│       ├── main.jsx               # React mount root
│       └── index.css              # Dark developer studio theme
├── run-parser-tests.bat    # Windows test launcher
├── start-backend.bat       # Windows backend launcher
├── start-frontend.bat      # Windows frontend launcher
├── start-all.bat           # Launch both backend & frontend
├── package.json            # Root workspace scripts
└── README.md               # Complete lab documentation
```

---

## 7. Prerequisites & Environment Setup

### Windows Native

The project has been verified on Windows using:
- **Node.js:** v18+ (tested with v24.14)
- **GCC / Clang:** MinGW-w64 (LLVM-MinGW or WinLibs)
- **Flex & Bison:** WinFlexBison 2.5+
- **Make:** GNU Make 4.4+

Install via Windows Package Manager (`winget`):
```powershell
winget install WinFlexBison.win_flex_bison
winget install MartinStorsjo.LLVM-MinGW.UCRT
winget install ezwinports.make
```

### Ubuntu / Linux / WSL

On Linux or Windows Subsystem for Linux (WSL):
```bash
sudo apt-get update
sudo apt-get install -y gcc flex bison make nodejs npm
```

---

## 8. Build and Execution Guide

### 1. Compile the Parser Engine

Inside the `parser/` directory:
```bash
cd parser
make all
```
This generates:
- `parser.tab.c` and `parser.tab.h` (from Bison)
- `lex.yy.c` (from Flex)
- `basic_parser.exe` (or `basic_parser` on Linux)

To run the parser directly from the terminal:
```bash
# JSON output mode (default):
./basic_parser.exe --json tests/valid/01_hello_world.bas

# Tabular tokens mode:
./basic_parser.exe --tokens-only tests/valid/01_hello_world.bas
```

### 2. Start the Backend API

```bash
cd backend
npm install
npm start
```
The backend starts on `http://localhost:5000`.  
Verify health: `http://localhost:5000/api/health`

### 3. Start the Frontend Studio

```bash
cd frontend
npm install
npm run dev
```
The React frontend starts on `http://localhost:3000`. Open your browser to begin testing.

---

## 9. Automated Testing Suite

The project includes automated test suites for both the parser engine and the REST API:

### 1. Parser Automated Test Suite (21 Tests)
Run from root:
```bash
node parser/run_tests.js
```
Output:
```text
====================================================
       BASIC PARSER AUTOMATED TEST SUITE            
====================================================

--- Testing Valid BASIC Programs (Expected: ACCEPTED) ---
  [PASS] 01_hello_world.bas -> Tokens: 3, Errors: 0
  [PASS] 02_assignments.bas -> Tokens: 15, Errors: 0
  [PASS] 03_literals_and_strings.bas -> Tokens: 24, Errors: 0
  [PASS] 04_arithmetic_precedence.bas -> Tokens: 21, Errors: 0
  [PASS] 05_input_output.bas -> Tokens: 19, Errors: 0
  [PASS] 06_if_multiline.bas -> Tokens: 48, Errors: 0
  [PASS] 07_if_single_line.bas -> Tokens: 19, Errors: 0
  [PASS] 08_for_loop_step.bas -> Tokens: 18, Errors: 0
  [PASS] 09_while_loop.bas -> Tokens: 22, Errors: 0
  [PASS] 10_nested_statements.bas -> Tokens: 44, Errors: 0
  [PASS] 11_colons_and_line_numbers.bas -> Tokens: 29, Errors: 0
  [PASS] 12_comments_and_empty.bas -> Tokens: 13, Errors: 0

--- Testing Invalid BASIC Programs (Expected: REJECTED) ---
  [PASS] 01_missing_expr.bas -> Caught 1 error(s)
  [PASS] 02_unmatched_paren.bas -> Caught 1 error(s)
  [PASS] 03_missing_end_if.bas -> Caught 1 error(s)
  [PASS] 04_malformed_for.bas -> Caught 1 error(s)
  [PASS] 05_missing_wend.bas -> Caught 1 error(s)
  [PASS] 06_invalid_operator.bas -> Caught 1 error(s)
  [PASS] 07_unterminated_string.bas -> Caught 1 error(s)
  [PASS] 08_invalid_character.bas -> Caught 2 error(s)
  [PASS] 09_malformed_input.bas -> Caught 1 error(s)

====================================================
Results: 21/21 Passed (0 Failed)
====================================================
```

### 2. Backend API Test Suite (18 Tests)
```bash
cd backend
npm test
```
Tests health endpoints, example loaders, parsing endpoints, error responses, and validates all 13 sample programs through the API.

---

## 10. Sample Programs

### Valid Example: Arithmetic Precedence
```basic
REM Operator Precedence Test
LET RESULT = 2 + 3 * 4 ^ 2 - (10 / 2) MOD 3
PRINT "Result: "; RESULT
```

**AST Representation:**
```text
Program
└── AssignmentStatement (RESULT, hasLet=true)
    └── BinaryExpression (-)
        ├── BinaryExpression (+)
        │   ├── NumberLiteral (2)
        │   └── BinaryExpression (*)
        │       ├── NumberLiteral (3)
        │       └── BinaryExpression (^)
        │           ├── NumberLiteral (4)
        │           └── NumberLiteral (2)
        └── BinaryExpression (MOD)
            ├── BinaryExpression (/)
            │   ├── NumberLiteral (10)
            │   └── NumberLiteral (2)
            └── NumberLiteral (3)
```

### Invalid Example: Missing `END IF`
```basic
IF TEMPERATURE > 100 THEN
    PRINT "Warning: Overheating!"
```
**Diagnostic Output:**
```json
{
  "type": "SYNTAX_ERROR",
  "message": "Syntax error: unexpected end of statement or token",
  "line": 2,
  "column": 33,
  "snippet": "    PRINT \"Warning: Overheating!\""
}
```

---

## 11. College Lab Presentation Demonstration Workflow

When presenting this project in a viva or demonstration:

1. **Start Services:** Run `start-all.bat` or launch backend and frontend.
2. **Explain the Interface:**
   - Left pane: Monaco Editor with syntax highlighting and example selector.
   - Right pane: Parser status banner, Abstract Syntax Tree, Tokens table, Diagnostics, and Grammar tabs.
3. **Demo 1 — Valid Basic Program:**
   - Load `1. Hello World` or `2. Variable Assignments`.
   - Click **Parse**.
   - Show the **Tokens Tab**: demonstrate token categorization, filtering, and exact line/column tracking.
   - Show the **AST Tab**: expand and collapse nodes, click a node to view attributes in the Node Inspector.
4. **Demo 2 — Operator Precedence:**
   - Load `3. Arithmetic & Operator Precedence` (`RESULT = 2 + 3 * 4 ^ 2`).
   - Open the **AST Tab**: point out that `4 ^ 2` is grouped first, then multiplied by `3`, and finally added to `2`, proving that the Bison operator precedence rules work properly.
5. **Demo 3 — Syntax & Lexical Error Handling:**
   - Load `11. Error: Unmatched Parentheses` or `13. Error: Unterminated String`.
   - Click **Parse**.
   - Show the **Diagnostics Tab**: point out the red snippet preview with the caret pointer (`^`) marking the exact error column, and explain the compiler guidance tip.
6. **Demo 4 — Grammar & Architecture:**
   - Open the **Grammar Reference Tab** and explain the context-free grammar production rules in BNF.
   - Click the **About** button in the navbar to walk through the 5-phase compiler architecture pipeline.

---

## 12. Troubleshooting & FAQs

### Q: Why does the parser report "unexpected end of statement"?
**A:** In BASIC, blocks such as `IF`, `FOR`, and `WHILE` require explicit terminators (`END IF`, `NEXT`, `WEND`). Ensure all opened blocks are properly closed.

### Q: Can I run this without installing MinGW or Bison locally?
**A:** The compiled binary `parser/basic_parser.exe` is pre-compiled for Windows. As long as Node.js is installed, you can run the backend and frontend immediately.

### Q: Does the studio run BASIC programs?
**A:** No. This is a front-end compiler tool (lexical and syntax analysis). It builds the Abstract Syntax Tree; it does not interpret or generate machine code.

---

## 📜 License & Acknowledgments
Created as a comprehensive Compiler Design Lab project adhering to standard compiler construction principles using **Flex**, **GNU Bison**, **C11**, **Node.js**, **Express**, and **React**.

