const examples = [
    {
        id: "hello-world",
        name: "1. Hello World",
        category: "Basics",
        description: "Simple program demonstrating the PRINT statement and string literal output.",
        expectedStatus: "ACCEPTED",
        code: `REM Welcome to BASIC Parser Studio!
PRINT "Hello, World!"
PRINT "Compiler Design Lab - BASIC Language Parser"
`
    },
    {
        id: "assignments",
        name: "2. Variable Assignments",
        category: "Variables",
        description: "Variables with and without the optional LET keyword, plus string variable ($).",
        expectedStatus: "ACCEPTED",
        code: `REM Variable Assignments
LET A = 100
B = 250
SUM = A + B
LABEL$ = "Sum calculation"

PRINT LABEL$; ": "; SUM
`
    },
    {
        id: "arithmetic-precedence",
        name: "3. Arithmetic & Operator Precedence",
        category: "Expressions",
        description: "Shows correct precedence: Power (^) > Multiply/Divide (*) > Add/Subtract (+).",
        expectedStatus: "ACCEPTED",
        code: `REM Operator Precedence in BASIC
LET RESULT = 2 + 3 * 4 ^ 2 - (10 / 2) MOD 3
PRINT "Evaluated Expression Result: "; RESULT
`
    },
    {
        id: "input-output",
        name: "4. Interactive Input & Output",
        category: "I/O",
        description: "INPUT statement with custom prompt message and comma/semicolon printing.",
        expectedStatus: "ACCEPTED",
        code: `INPUT "Enter your student name: "; USERNAME$
INPUT "Enter your age: "; AGE
PRINT "Student: "; USERNAME$
PRINT "Registered age: "; AGE
`
    },
    {
        id: "if-multiline",
        name: "5. Multiline IF-THEN-ELSE",
        category: "Conditionals",
        description: "Structured multiline conditional branching with ELSEIF and ELSE.",
        expectedStatus: "ACCEPTED",
        code: `LET SCORE = 85

IF SCORE >= 90 THEN
    GRADE$ = "A - Excellent"
ELSEIF SCORE >= 80 THEN
    GRADE$ = "B - Good"
ELSEIF SCORE >= 70 THEN
    GRADE$ = "C - Satisfactory"
ELSE
    GRADE$ = "F - Needs Improvement"
END IF

PRINT "Final Grade: "; GRADE$
`
    },
    {
        id: "if-single-line",
        name: "6. Single-line IF Statements",
        category: "Conditionals",
        description: "Traditional BASIC inline conditional statements with optional inline ELSE.",
        expectedStatus: "ACCEPTED",
        code: `LET X = 15
IF X > 10 THEN PRINT "X is greater than 10"
IF X = 15 THEN PRINT "X is exactly 15" ELSE PRINT "X is not 15"
`
    },
    {
        id: "for-loop",
        name: "7. FOR-NEXT Loop with STEP",
        category: "Loops",
        description: "Counting loop with start, end, and negative step decrement.",
        expectedStatus: "ACCEPTED",
        code: `REM Countdown Rocket Launch
FOR T = 10 TO 1 STEP -1
    PRINT "T-minus "; T; " seconds..."
NEXT T

PRINT "Liftoff!"
`
    },
    {
        id: "while-loop",
        name: "8. WHILE-WEND Loop",
        category: "Loops",
        description: "Indefinite iteration using condition check and WEND boundary.",
        expectedStatus: "ACCEPTED",
        code: `COUNTER = 1
TOTAL = 0

WHILE COUNTER <= 5
    TOTAL = TOTAL + COUNTER
    PRINT "Step "; COUNTER; " Sum: "; TOTAL
    COUNTER = COUNTER + 1
WEND

PRINT "Final Total: "; TOTAL
`
    },
    {
        id: "nested-constructs",
        name: "9. Nested Loops & Conditionals",
        category: "Advanced",
        description: "Nested 2D matrix coordinate loop with conditional classification.",
        expectedStatus: "ACCEPTED",
        code: `FOR ROW = 1 TO 3
    FOR COL = 1 TO 3
        IF ROW = COL THEN
            PRINT "Diagonal element at ["; ROW; ","; COL; "]"
        ELSE
            PRINT "Off-diagonal element at ["; ROW; ","; COL; "]"
        END IF
    NEXT COL
NEXT ROW
`
    },
    {
        id: "line-numbers-colons",
        name: "10. Line Numbers & Colons",
        category: "Advanced",
        description: "Classic Dartmouth / QBASIC numbered lines and multiple statements on one line separated by colons.",
        expectedStatus: "ACCEPTED",
        code: `10 LET X = 10 : Y = 20 : Z = X + Y
20 PRINT "Values: "; X; Y; Z
30 IF Z > 25 THEN GOTO 50
40 PRINT "Z is small" : END
50 PRINT "Z is large!"
60 END
`
    },
    {
        id: "error-unmatched-paren",
        name: "11. Error: Unmatched Parentheses",
        category: "Diagnostics",
        description: "Demonstrates syntax error detection for unclosed expression parentheses.",
        expectedStatus: "REJECTED",
        code: `REM Intentionally malformed expression
LET RESULT = (10 + 20 * (5 - 2)
PRINT RESULT
`
    },
    {
        id: "error-missing-end-if",
        name: "12. Error: Missing END IF",
        category: "Diagnostics",
        description: "Demonstrates syntax error detection when a multiline block is unclosed.",
        expectedStatus: "REJECTED",
        code: `IF TEMPERATURE > 100 THEN
    PRINT "Warning: Overheating!"
`
    },
    {
        id: "error-unterminated-string",
        name: "13. Error: Unterminated String",
        category: "Diagnostics",
        description: "Demonstrates lexical analysis error detection for an unclosed string quote.",
        expectedStatus: "REJECTED",
        code: `PRINT "This string is never closed
PRINT "Next line"
`
    }
];

module.exports = examples;

