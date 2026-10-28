import React from 'react';
import { BookOpen, Table, ShieldAlert, Cpu, Terminal, ArrowRight } from 'lucide-react';

export default function GrammarTab() {
  return (
    <div className="p-3" style={{ maxHeight: 'calc(100vh - 240px)', overflowY: 'auto' }}>
      {/* Intro Header */}
      <div className="mb-4">
        <h5 className="text-light fw-bold d-flex align-items-center gap-2">
          <BookOpen size={20} className="text-info" />
          Supported BASIC Dialect & Context-Free Grammar
        </h5>
        <p className="text-secondary" style={{ fontSize: '0.88rem' }}>
          This educational parser implements a clean subset of traditional, Dartmouth / QBASIC-style BASIC. Below are the actual production rules implemented in GNU Bison and the lexical tokens recognized by Flex.
        </p>
      </div>

      {/* Operator Precedence Table */}
      <div className="grammar-section mb-4">
        <h6 className="text-light fw-bold mb-3 d-flex align-items-center gap-2">
          <Table size={16} className="text-warning" />
          Operator Precedence & Associativity Hierarchy
        </h6>
        <div className="table-responsive">
          <table className="table table-dark table-sm table-bordered mb-0" style={{ fontSize: '0.82rem' }}>
            <thead>
              <tr className="table-active">
                <th>Level</th>
                <th>Operator(s)</th>
                <th>Description</th>
                <th>Associativity</th>
              </tr>
            </thead>
            <tbody>
              <tr>
                <td>1 (Highest)</td>
                <td><code>^</code></td>
                <td>Exponentiation</td>
                <td>Right-to-Left (e.g. <code>2 ^ 3 ^ 2 = 512</code>)</td>
              </tr>
              <tr>
                <td>2</td>
                <td><code>+ (unary)</code>, <code>- (unary)</code></td>
                <td>Unary Plus and Minus</td>
                <td>Right-to-Left</td>
              </tr>
              <tr>
                <td>3</td>
                <td><code>*</code>, <code>/</code>, <code>\</code>, <code>MOD</code></td>
                <td>Multiplication, Real Division, Integer Division, Modulo</td>
                <td>Left-to-Right</td>
              </tr>
              <tr>
                <td>4</td>
                <td><code>+</code>, <code>-</code></td>
                <td>Addition and Subtraction</td>
                <td>Left-to-Right</td>
              </tr>
              <tr>
                <td>5</td>
                <td><code>=</code>, <code>&lt;&gt;</code>, <code>&lt;</code>, <code>&gt;</code>, <code>&lt;=</code>, <code>&gt;=</code></td>
                <td>Relational comparisons (equal, not equal, less, greater)</td>
                <td>Non-associative</td>
              </tr>
              <tr>
                <td>6</td>
                <td><code>NOT</code></td>
                <td>Logical Negation</td>
                <td>Right-to-Left</td>
              </tr>
              <tr>
                <td>7</td>
                <td><code>AND</code></td>
                <td>Logical Conjunction</td>
                <td>Left-to-Right</td>
              </tr>
              <tr>
                <td>8 (Lowest)</td>
                <td><code>OR</code></td>
                <td>Logical Disjunction</td>
                <td>Left-to-Right</td>
              </tr>
            </tbody>
          </table>
        </div>
      </div>

      {/* Context-Free Grammar Rules */}
      <div className="grammar-section mb-4">
        <h6 className="text-light fw-bold mb-3 d-flex align-items-center gap-2">
          <Terminal size={16} className="text-primary" />
          Context-Free Grammar Production Rules (BNF)
        </h6>

        {/* 1. Program and Lines */}
        <div className="mb-3">
          <div className="text-info fw-semibold mb-1" style={{ fontSize: '0.85rem' }}>1. Program & Line Boundaries</div>
          <pre className="grammar-rule">
{`program             ::= lines

lines               ::= ε
                      | lines line

line                ::= EOL
                      | [ line_label ] statements_on_line EOL

line_label          ::= INT_LITERAL

statements_on_line  ::= statement
                      | statements_on_line ':' statement`}
          </pre>
        </div>

        {/* 2. Statements */}
        <div className="mb-3">
          <div className="text-info fw-semibold mb-1" style={{ fontSize: '0.85rem' }}>2. Statements</div>
          <pre className="grammar-rule">
{`statement           ::= assignment_stmt
                      | print_stmt
                      | input_stmt
                      | if_stmt
                      | for_stmt
                      | while_stmt
                      | goto_stmt
                      | gosub_stmt
                      | return_stmt
                      | end_stmt
                      | stop_stmt`}
          </pre>
        </div>

        {/* 3. Assignment and I/O */}
        <div className="mb-3">
          <div className="text-info fw-semibold mb-1" style={{ fontSize: '0.85rem' }}>3. Assignment and Input/Output</div>
          <pre className="grammar-rule">
{`assignment_stmt     ::= [ LET ] IDENTIFIER '=' expression

print_stmt          ::= PRINT [ print_item_list ] [ ',' | ';' ]

print_item_list     ::= print_item
                      | print_item_list ( ',' | ';' ) print_item

print_item          ::= expression

input_stmt          ::= INPUT var_list
                      | INPUT STRING_LITERAL ( ';' | ',' ) var_list

var_list            ::= IDENTIFIER
                      | var_list ',' IDENTIFIER`}
          </pre>
        </div>

        {/* 4. Conditionals & Loops */}
        <div className="mb-3">
          <div className="text-info fw-semibold mb-1" style={{ fontSize: '0.85rem' }}>4. Conditionals and Loops</div>
          <pre className="grammar-rule">
{`if_stmt             ::= IF expression THEN EOL block_lines [ else_clause ] END IF
                      | IF expression THEN statement [ ELSE statement ]

else_clause         ::= ELSE EOL block_lines
                      | ELSEIF expression THEN EOL block_lines [ else_clause ]

for_stmt            ::= FOR IDENTIFIER '=' expression TO expression [ STEP expression ] EOL
                            block_lines
                        NEXT [ IDENTIFIER ]

while_stmt          ::= WHILE expression EOL
                            block_lines
                        WEND`}
          </pre>
        </div>

        {/* 5. Control flow */}
        <div className="mb-3">
          <div className="text-info fw-semibold mb-1" style={{ fontSize: '0.85rem' }}>5. Control Flow Statements</div>
          <pre className="grammar-rule">
{`goto_stmt           ::= GOTO ( INT_LITERAL | IDENTIFIER )
gosub_stmt          ::= GOSUB ( INT_LITERAL | IDENTIFIER )
return_stmt         ::= RETURN
end_stmt            ::= END
stop_stmt           ::= STOP`}
          </pre>
        </div>
      </div>

      {/* Lexical Tokens Specification */}
      <div className="grammar-section mb-4">
        <h6 className="text-light fw-bold mb-3 d-flex align-items-center gap-2">
          <Cpu size={16} className="text-success" />
          Lexical Token Specifications (Flex)
        </h6>
        <div className="table-responsive">
          <table className="table table-dark table-sm table-bordered mb-0" style={{ fontSize: '0.82rem' }}>
            <thead>
              <tr className="table-active">
                <th>Category</th>
                <th>Flex Regular Expression Pattern</th>
                <th>Examples</th>
              </tr>
            </thead>
            <tbody>
              <tr>
                <td>Keywords</td>
                <td><code>LET | PRINT | ? | INPUT | IF | THEN | ELSE | ELSEIF | END[ \t]+IF | ENDIF | FOR | TO | STEP | NEXT | WHILE | WEND | GOTO | GOSUB | RETURN | END | STOP | AND | OR | NOT | MOD</code></td>
                <td><code>PRINT, FOR, WHILE, END IF</code></td>
              </tr>
              <tr>
                <td>Identifiers</td>
                <td><code>[a-zA-Z][a-zA-Z0-9_]*[$%!]?</code></td>
                <td><code>X, NAME$, COUNT%, RADIUS</code></td>
              </tr>
              <tr>
                <td>Integers</td>
                <td><code>[0-9]+</code></td>
                <td><code>10, 42, 1000</code></td>
              </tr>
              <tr>
                <td>Floats</td>
                <td><code>([0-9]+\.[0-9]*|\.[0-9]+)([eE][+-]?[0-9]+)?</code></td>
                <td><code>3.14159, .5, 1.2e-4</code></td>
              </tr>
              <tr>
                <td>Strings</td>
                <td><code>\"([^\"\\\r\n]|\\.)*\"</code></td>
                <td><code>"Hello World"</code></td>
              </tr>
              <tr>
                <td>Comments</td>
                <td><code>REM([ \t][^\r\n]*)? | '[^\r\n]*</code></td>
                <td><code>REM comment, ' remark</code></td>
              </tr>
            </tbody>
          </table>
        </div>
      </div>

      {/* Scope and Known Limitations */}
      <div className="grammar-section">
        <h6 className="text-light fw-bold mb-2 d-flex align-items-center gap-2">
          <ShieldAlert size={16} className="text-danger" />
          Scope & Known Limitations
        </h6>
        <ul className="text-secondary mb-0" style={{ fontSize: '0.84rem' }}>
          <li><strong>Syntax Analyzer Only:</strong> This application performs lexical and syntax analysis. It constructs the Abstract Syntax Tree (AST); it does NOT interpret or execute BASIC runtime code.</li>
          <li><strong>Unsupported constructs:</strong> Advanced system features like disk file I/O (<code>OPEN ... FOR INPUT</code>), hardware memory commands (<code>PEEK, POKE</code>), and graphical instructions (<code>SCREEN, LINE, CIRCLE</code>) are out of scope for this syntax lab.</li>
          <li><strong>Case Insensitivity:</strong> Keywords are recognized case-insensitively (e.g., <code>print</code>, <code>Print</code>, and <code>PRINT</code> are identical).</li>
        </ul>
      </div>
    </div>
  );
}

