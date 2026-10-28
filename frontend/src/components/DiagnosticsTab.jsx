import React from 'react';
import { AlertCircle, CheckCircle, HelpCircle, Code, MapPin } from 'lucide-react';

function getTipForError(msg) {
  const m = msg.toLowerCase();
  if (m.includes('unexpected end') || m.includes('incomplete')) {
    return 'Check if you have an unclosed IF (missing END IF), unclosed WHILE (missing WEND), unclosed FOR (missing NEXT), or an incomplete expression.';
  }
  if (m.includes('unterminated string')) {
    return 'Ensure all double-quoted strings have a matching closing quote (") before the end of the line.';
  }
  if (m.includes('invalid character')) {
    return 'The character is not part of the BASIC character set. Identifiers only contain letters, numbers, and suffixes like $, %, !.';
  }
  if (m.includes('syntax error near')) {
    return 'Check for consecutive binary operators (e.g., "+ *"), missing operands, or misplaced keywords.';
  }
  return 'Review the BASIC language grammar tab for the expected syntax of this statement.';
}

export default function DiagnosticsTab({ diagnostics, isSuccess }) {
  if (isSuccess && (!diagnostics || diagnostics.length === 0)) {
    return (
      <div className="p-4 text-center">
        <div className="d-inline-flex p-3 rounded-circle bg-success-subtle text-success mb-3">
          <CheckCircle size={36} />
        </div>
        <h5 className="text-light fw-bold">No Errors Detected</h5>
        <p className="text-secondary" style={{ maxWidth: '450px', margin: '0 auto', fontSize: '0.88rem' }}>
          The submitted program successfully passed both Lexical Analysis (Flex) and Syntax Analysis (Bison). The Abstract Syntax Tree (AST) has been generated.
        </p>
      </div>
    );
  }

  if (!diagnostics || diagnostics.length === 0) {
    return (
      <div className="p-4 text-center text-secondary">
        <AlertCircle size={32} className="mb-2 opacity-50" />
        <p>No diagnostics recorded yet. Run <strong>Parse</strong> to inspect syntax.</p>
      </div>
    );
  }

  return (
    <div className="p-3" style={{ maxHeight: 'calc(100vh - 240px)', overflowY: 'auto' }}>
      <div className="d-flex align-items-center justify-content-between mb-3">
        <div className="d-flex align-items-center gap-2">
          <AlertCircle size={18} className="text-danger" />
          <h6 className="text-light mb-0 fw-semibold">
            {diagnostics.length} Diagnostic Issue{diagnostics.length === 1 ? '' : 's'} Reported
          </h6>
        </div>
        <span className="badge bg-danger-subtle text-danger border border-danger-subtle">
          Syntax Analysis Failed
        </span>
      </div>

      {diagnostics.map((diag, index) => {
        const isLexical = diag.type === 'LEXICAL_ERROR';
        const tip = getTipForError(diag.message);

        // Build caret pointer for snippet
        const col = Math.max(1, diag.column || 1);
        const caretSpaces = ' '.repeat(col - 1);

        return (
          <div key={index} className="diag-card">
            {/* Header: Type and Location */}
            <div className="d-flex align-items-center justify-content-between flex-wrap gap-2">
              <div className="d-flex align-items-center gap-2">
                <span className={`badge ${isLexical ? 'bg-warning text-dark' : 'bg-danger text-white'}`} style={{ fontSize: '0.72rem' }}>
                  {isLexical ? 'LEXICAL ERROR' : 'SYNTAX ERROR'}
                </span>
                <span className="fw-semibold text-light" style={{ fontSize: '0.9rem' }}>
                  {diag.message}
                </span>
              </div>
              <div className="d-flex align-items-center gap-1 text-secondary" style={{ fontSize: '0.78rem' }}>
                <MapPin size={13} className="text-danger" />
                <span>Line <strong>{diag.line}</strong>, Column <strong>{diag.column}</strong></span>
              </div>
            </div>

            {/* Code Snippet with Pointer */}
            {diag.snippet && (
              <div className="diag-snippet mt-2">
                <div className="text-secondary mb-1" style={{ fontSize: '0.72rem' }}>
                  Line {diag.line}:
                </div>
                <div>{diag.snippet}</div>
                <div className="text-danger fw-bold" style={{ lineHeight: 1 }}>
                  {caretSpaces}^
                </div>
              </div>
            )}

            {/* Educational compiler tip */}
            <div className="d-flex align-items-start gap-1.5 mt-2 text-secondary" style={{ fontSize: '0.8rem' }}>
              <HelpCircle size={14} className="text-info flex-shrink-0 mt-0.5" />
              <span><strong>Compiler Tip:</strong> {tip}</span>
            </div>
          </div>
        );
      })}
    </div>
  );
}

