import React from 'react';
import { CheckCircle2, XCircle, Clock, Hash, AlertTriangle, Layers, FileText } from 'lucide-react';

export default function StatsBanner({ result, loading }) {
  if (loading) {
    return (
      <div className="stats-banner py-2">
        <div className="d-flex align-items-center gap-2 text-warning">
          <span className="spinner-border spinner-border-sm" role="status"></span>
          <span>Lexical and syntax analysis in progress...</span>
        </div>
      </div>
    );
  }

  if (!result) {
    return (
      <div className="stats-banner py-2 text-secondary">
        <span>Click <strong>Parse</strong> to run the Flex Lexer & Bison Parser.</span>
      </div>
    );
  }

  const isAccepted = result.success === true && result.status === 'ACCEPTED';
  const tokenCount = result.statistics?.tokenCount ?? result.tokens?.length ?? 0;
  const errorCount = result.statistics?.errorCount ?? result.diagnostics?.length ?? 0;
  const execTime = result.executionTimeMs ?? 0;
  const lineCount = result.statistics?.lineCount ?? 0;

  // Count AST nodes recursively
  const countAstNodes = (node) => {
    if (!node) return 0;
    let count = 1;
    if (node.statements && Array.isArray(node.statements)) {
      node.statements.forEach(child => count += countAstNodes(child));
    }
    if (node.items && Array.isArray(node.items)) {
      node.items.forEach(child => count += countAstNodes(child));
    }
    if (node.value && typeof node.value === 'object') {
      count += countAstNodes(node.value);
    }
    if (node.left) count += countAstNodes(node.left);
    if (node.right) count += countAstNodes(node.right);
    if (node.operand) count += countAstNodes(node.operand);
    if (node.condition) count += countAstNodes(node.condition);
    if (node.thenBranch) count += countAstNodes(node.thenBranch);
    if (node.elseBranch) count += countAstNodes(node.elseBranch);
    if (node.body) count += countAstNodes(node.body);
    if (node.statement) count += countAstNodes(node.statement);
    return count;
  };

  const astNodeCount = result.ast ? countAstNodes(result.ast) : 0;

  return (
    <div className="stats-banner justify-content-between">
      {/* Status indicator */}
      <div className="d-flex align-items-center gap-2">
        {isAccepted ? (
          <div className="d-flex align-items-center gap-1.5 px-2.5 py-1 rounded bg-success-subtle text-success border border-success-subtle fw-semibold">
            <CheckCircle2 size={15} />
            <span>PARSE ACCEPTED</span>
          </div>
        ) : (
          <div className="d-flex align-items-center gap-1.5 px-2.5 py-1 rounded bg-danger-subtle text-danger border border-danger-subtle fw-semibold">
            <XCircle size={15} />
            <span>PARSE REJECTED ({errorCount} error{errorCount === 1 ? '' : 's'})</span>
          </div>
        )}
      </div>

      {/* Statistics metrics */}
      <div className="d-flex align-items-center gap-4 flex-wrap">
        <div className="stat-chip" title="Total Tokens produced by Flex Lexer">
          <Hash size={14} className="text-info" />
          <span className="text-secondary">Tokens:</span>
          <strong className="text-light">{tokenCount}</strong>
        </div>

        {isAccepted && (
          <div className="stat-chip" title="Total nodes in Abstract Syntax Tree">
            <Layers size={14} className="text-warning" />
            <span className="text-secondary">AST Nodes:</span>
            <strong className="text-light">{astNodeCount}</strong>
          </div>
        )}

        <div className="stat-chip" title="Total Errors">
          <AlertTriangle size={14} className={errorCount > 0 ? "text-danger" : "text-success"} />
          <span className="text-secondary">Errors:</span>
          <strong className={errorCount > 0 ? "text-danger" : "text-success"}>{errorCount}</strong>
        </div>

        <div className="stat-chip" title="Source Lines Analyzed">
          <FileText size={14} className="text-primary" />
          <span className="text-secondary">Lines:</span>
          <strong className="text-light">{lineCount}</strong>
        </div>

        <div className="stat-chip" title="Parser Execution Time">
          <Clock size={14} className="text-secondary" />
          <span className="text-secondary">Time:</span>
          <strong className="text-light">{execTime} ms</strong>
        </div>
      </div>
    </div>
  );
}

