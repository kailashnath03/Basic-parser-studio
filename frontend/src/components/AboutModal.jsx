import React from 'react';
import { X, GraduationCap, Cpu, GitBranch, Layers, CheckCircle2, ArrowRight } from 'lucide-react';

export default function AboutModal({ isOpen, onClose }) {
  if (!isOpen) return null;

  return (
    <div 
      className="modal show d-block" 
      tabIndex="-1" 
      style={{ backgroundColor: 'rgba(0, 0, 0, 0.75)', backdropFilter: 'blur(4px)', zIndex: 1060 }}
    >
      <div className="modal-dialog modal-lg modal-dialog-centered modal-dialog-scrollable">
        <div className="modal-content bg-dark text-light border border-secondary shadow-lg">
          {/* Header */}
          <div className="modal-header border-secondary py-3 px-4">
            <div className="d-flex align-items-center gap-2">
              <GraduationCap size={22} className="text-warning" />
              <h5 className="modal-title fw-bold text-white mb-0">
                Compiler Design Lab — BASIC Parser Studio
              </h5>
            </div>
            <button 
              type="button" 
              className="btn-close btn-close-white" 
              onClick={onClose}
              aria-label="Close"
            ></button>
          </div>

          {/* Body */}
          <div className="modal-body p-4" style={{ fontSize: '0.9rem', lineHeight: '1.6' }}>
            {/* Objective Banner */}
            <div className="p-3 rounded mb-4" style={{ backgroundColor: 'rgba(124, 58, 237, 0.1)', border: '1px solid rgba(124, 58, 237, 0.3)' }}>
              <h6 className="fw-bold text-white mb-1">Project Objective</h6>
              <p className="text-secondary mb-0" style={{ fontSize: '0.86rem' }}>
                Demonstrate the fundamental phases of front-end compiler construction: lexical analysis, syntax analysis, and Abstract Syntax Tree (AST) synthesis for the <strong>BASIC (Beginner's All-purpose Symbolic Instruction Code)</strong> programming language using industry-standard tools: <strong>Flex</strong> and <strong>GNU Bison</strong> in Yacc-compatible mode.
              </p>
            </div>

            {/* End-to-End Compiler Pipeline */}
            <h6 className="text-light fw-bold mb-3 d-flex align-items-center gap-2">
              <GitBranch size={17} className="text-info" />
              Compiler Architecture & Data Flow
            </h6>

            <div className="d-flex flex-column gap-2 mb-4">
              <div className="p-2.5 rounded bg-black border border-secondary d-flex align-items-center gap-3">
                <span className="badge bg-primary text-white" style={{ width: '80px' }}>Phase 1</span>
                <div>
                  <strong className="text-light">Lexical Analysis (Flex — lexer.l)</strong>
                  <div className="text-secondary" style={{ fontSize: '0.8rem' }}>
                    Scans raw BASIC source code character-by-character using regular expressions. Generates a token stream with token types, lexemes, lines, and columns while stripping whitespace and handling remarks.
                  </div>
                </div>
              </div>

              <div className="text-center text-secondary py-0">
                <ArrowRight size={16} className="rotate-90" style={{ transform: 'rotate(90deg)' }} />
              </div>

              <div className="p-2.5 rounded bg-black border border-secondary d-flex align-items-center gap-3">
                <span className="badge bg-warning text-dark" style={{ width: '80px' }}>Phase 2</span>
                <div>
                  <strong className="text-light">Syntax Analysis (GNU Bison — parser.y)</strong>
                  <div className="text-secondary" style={{ fontSize: '0.8rem' }}>
                    Constructs an LALR(1) parsing table from context-free grammar production rules. Enforces operator precedence, resolves single-line vs multiline block structures with 0 conflicts, and detects syntax errors.
                  </div>
                </div>
              </div>

              <div className="text-center text-secondary py-0">
                <ArrowRight size={16} className="rotate-90" style={{ transform: 'rotate(90deg)' }} />
              </div>

              <div className="p-2.5 rounded bg-black border border-secondary d-flex align-items-center gap-3">
                <span className="badge bg-success text-white" style={{ width: '80px' }}>Phase 3</span>
                <div>
                  <strong className="text-light">Abstract Syntax Tree (ast.c / ast.h)</strong>
                  <div className="text-secondary" style={{ fontSize: '0.8rem' }}>
                    Semantic action blocks allocate heap memory in C to construct recursive AST nodes for expressions, assignments, loops, conditionals, and I/O statements. Serializes output to clean JSON.
                  </div>
                </div>
              </div>

              <div className="text-center text-secondary py-0">
                <ArrowRight size={16} className="rotate-90" style={{ transform: 'rotate(90deg)' }} />
              </div>

              <div className="p-2.5 rounded bg-black border border-secondary d-flex align-items-center gap-3">
                <span className="badge bg-info text-dark" style={{ width: '80px' }}>Phase 4 & 5</span>
                <div>
                  <strong className="text-light">Backend API & React Studio</strong>
                  <div className="text-secondary" style={{ fontSize: '0.8rem' }}>
                    Node.js & Express securely execute the native parser CLI via <code>child_process.spawn</code>. The React frontend presents tokens, interactive AST trees, and diagnostic snippet previews.
                  </div>
                </div>
              </div>
            </div>

            {/* Core Definitions */}
            <h6 className="text-light fw-bold mb-3 d-flex align-items-center gap-2">
              <Layers size={17} className="text-success" />
              Key Concepts & Definitions
            </h6>
            <div className="row g-3">
              <div className="col-md-6">
                <div className="p-3 rounded bg-black border border-secondary h-100">
                  <strong className="text-info">Token:</strong>
                  <p className="text-secondary mb-0 mt-1" style={{ fontSize: '0.82rem' }}>
                    The smallest syntactic unit produced during lexical analysis, comprising a token type (e.g., <code>KEYWORD_PRINT</code>) and the matched lexeme (e.g., <code>PRINT</code>).
                  </p>
                </div>
              </div>
              <div className="col-md-6">
                <div className="p-3 rounded bg-black border border-secondary h-100">
                  <strong className="text-warning">Context-Free Grammar (CFG):</strong>
                  <p className="text-secondary mb-0 mt-1" style={{ fontSize: '0.82rem' }}>
                    A formal set of production rules that define the valid phrase and statement structures of the language without ambiguity.
                  </p>
                </div>
              </div>
              <div className="col-md-6">
                <div className="p-3 rounded bg-black border border-secondary h-100">
                  <strong className="text-success">Abstract Syntax Tree (AST):</strong>
                  <p className="text-secondary mb-0 mt-1" style={{ fontSize: '0.82rem' }}>
                    A tree representation of the abstract syntactic structure of source code, omitting redundant punctuation while preserving operator precedence and nested blocks.
                  </p>
                </div>
              </div>
              <div className="col-md-6">
                <div className="p-3 rounded bg-black border border-secondary h-100">
                  <strong className="text-danger">Syntax Error:</strong>
                  <p className="text-secondary mb-0 mt-1" style={{ fontSize: '0.82rem' }}>
                    An error occurring when the token stream violates the grammar rules (e.g. unclosed parentheses, missing <code>END IF</code>, missing operands).
                  </p>
                </div>
              </div>
            </div>
          </div>

          {/* Footer */}
          <div className="modal-footer border-secondary py-2.5 px-4 d-flex justify-content-between">
            <span className="text-secondary" style={{ fontSize: '0.78rem' }}>
              Built with Flex, GNU Bison, C11, Node.js, Express & React
            </span>
            <button type="button" className="btn btn-secondary btn-sm px-3" onClick={onClose}>
              Close
            </button>
          </div>
        </div>
      </div>
    </div>
  );
}

