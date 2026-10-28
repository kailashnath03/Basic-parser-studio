import React, { useState } from 'react';
import { 
  ChevronRight, 
  ChevronDown, 
  Layers, 
  Code, 
  Copy, 
  Check, 
  Maximize2, 
  Minimize2, 
  Eye, 
  Tag, 
  Compass,
  FileCode
} from 'lucide-react';

const NODE_COLORS = {
  Program: { bg: 'rgba(139, 92, 246, 0.2)', border: '#8b5cf6', text: '#c4b5fd' },
  StatementList: { bg: 'rgba(99, 102, 241, 0.2)', border: '#6366f1', text: '#a5b4fc' },
  AssignmentStatement: { bg: 'rgba(6, 182, 212, 0.2)', border: '#06b6d4', text: '#67e8f9' },
  PrintStatement: { bg: 'rgba(59, 130, 246, 0.2)', border: '#3b82f6', text: '#93c5fd' },
  PrintItem: { bg: 'rgba(59, 130, 246, 0.15)', border: '#60a5fa', text: '#bfdbfe' },
  InputStatement: { bg: 'rgba(168, 85, 247, 0.2)', border: '#a855f7', text: '#d8b4fe' },
  IfStatement: { bg: 'rgba(16, 185, 129, 0.2)', border: '#10b981', text: '#6ee7b7' },
  ForStatement: { bg: 'rgba(245, 158, 11, 0.2)', border: '#f59e0b', text: '#fcd34d' },
  WhileStatement: { bg: 'rgba(234, 179, 8, 0.2)', border: '#eab308', text: '#fef08a' },
  BinaryExpression: { bg: 'rgba(244, 63, 94, 0.2)', border: '#f43f5e', text: '#fda4af' },
  UnaryExpression: { bg: 'rgba(236, 72, 153, 0.2)', border: '#ec4899', text: '#fbcfe8' },
  Variable: { bg: 'rgba(20, 184, 166, 0.2)', border: '#14b8a6', text: '#5eead4' },
  NumberLiteral: { bg: 'rgba(34, 197, 94, 0.2)', border: '#22c55e', text: '#86efac' },
  StringLiteral: { bg: 'rgba(249, 115, 22, 0.2)', border: '#f97316', text: '#fdba74' },
  LabeledStatement: { bg: 'rgba(120, 113, 108, 0.2)', border: '#78716c', text: '#d6d3d1' },
  GotoStatement: { bg: 'rgba(168, 85, 247, 0.2)', border: '#a855f7', text: '#e9d5ff' },
  GosubStatement: { bg: 'rgba(168, 85, 247, 0.2)', border: '#a855f7', text: '#e9d5ff' },
  ReturnStatement: { bg: 'rgba(107, 114, 128, 0.2)', border: '#6b7280', text: '#e5e7eb' },
  EndStatement: { bg: 'rgba(239, 68, 68, 0.2)', border: '#ef4444', text: '#fca5a5' },
  StopStatement: { bg: 'rgba(239, 68, 68, 0.2)', border: '#ef4444', text: '#fca5a5' }
};

function getNodeStyle(type) {
  return NODE_COLORS[type] || { bg: 'rgba(107, 114, 128, 0.2)', border: '#4b5563', text: '#d1d5db' };
}

function getNodeLabel(node) {
  if (!node) return 'null';
  switch (node.type) {
    case 'AssignmentStatement':
      return `${node.variable} = ... ${node.hasLet ? '(LET)' : ''}`;
    case 'BinaryExpression':
      return `Binary (${node.operator})`;
    case 'UnaryExpression':
      return `Unary (${node.operator})`;
    case 'Variable':
      return `Var: ${node.name}`;
    case 'NumberLiteral':
      return `Num: ${node.rawText ?? node.value}`;
    case 'StringLiteral':
      return `Str: "${node.value}"`;
    case 'IfStatement':
      return `IF (${node.isSingleLine ? 'inline' : 'block'})`;
    case 'ForStatement':
      return `FOR ${node.variable} = ...`;
    case 'WhileStatement':
      return 'WHILE ...';
    case 'LabeledStatement':
      return `Line ${node.lineNumber}`;
    case 'GotoStatement':
      return `GOTO ${node.targetLine || node.targetLabel}`;
    case 'GosubStatement':
      return `GOSUB ${node.targetLine || node.targetLabel}`;
    default:
      return node.type;
  }
}

function AstTreeNode({ node, level = 0, onSelectNode, selectedNode, globalExpanded }) {
  const [expanded, setExpanded] = useState(true);

  React.useEffect(() => {
    if (globalExpanded !== null) {
      setExpanded(globalExpanded);
    }
  }, [globalExpanded]);

  if (!node || typeof node !== 'object') return null;

  // Collect child nodes
  const children = [];

  if (node.statements && Array.isArray(node.statements)) {
    node.statements.forEach((stmt, i) => children.push({ key: `stmt-${i}`, label: `stmt[${i}]`, node: stmt }));
  }
  if (node.items && Array.isArray(node.items)) {
    node.items.forEach((item, i) => children.push({ key: `item-${i}`, label: `item[${i}]`, node: item }));
  }
  if (node.value && typeof node.value === 'object') {
    children.push({ key: 'val', label: 'value', node: node.value });
  }
  if (node.left) children.push({ key: 'left', label: 'left', node: node.left });
  if (node.right) children.push({ key: 'right', label: 'right', node: node.right });
  if (node.operand) children.push({ key: 'operand', label: 'operand', node: node.operand });
  if (node.condition) children.push({ key: 'cond', label: 'condition', node: node.condition });
  if (node.thenBranch) children.push({ key: 'then', label: 'thenBranch', node: node.thenBranch });
  if (node.elseBranch) children.push({ key: 'else', label: 'elseBranch', node: node.elseBranch });
  if (node.start) children.push({ key: 'start', label: 'start', node: node.start });
  if (node.end) children.push({ key: 'end', label: 'end', node: node.end });
  if (node.step) children.push({ key: 'step', label: 'step', node: node.step });
  if (node.body) children.push({ key: 'body', label: 'body', node: node.body });
  if (node.statement) children.push({ key: 'stmt', label: 'statement', node: node.statement });
  if (node.expression) children.push({ key: 'expr', label: 'expression', node: node.expression });
  if (node.variables && Array.isArray(node.variables)) {
    node.variables.forEach((v, i) => children.push({ key: `var-${i}`, label: `var[${i}]`, node: v }));
  }

  const hasChildren = children.length > 0;
  const isSelected = selectedNode === node;
  const style = getNodeStyle(node.type);

  return (
    <div className="ast-node">
      <div 
        className={`ast-node-header ${isSelected ? 'selected' : ''}`}
        onClick={() => onSelectNode(node)}
      >
        {hasChildren ? (
          <span 
            onClick={(e) => { e.stopPropagation(); setExpanded(!expanded); }} 
            className="text-secondary p-0.5"
            style={{ cursor: 'pointer' }}
          >
            {expanded ? <ChevronDown size={14} /> : <ChevronRight size={14} />}
          </span>
        ) : (
          <span style={{ display: 'inline-block', width: 14 }} />
        )}

        {/* Node Type Badge */}
        <span 
          style={{
            backgroundColor: style.bg,
            borderColor: style.border,
            color: style.text,
            borderWidth: '1px',
            borderStyle: 'solid',
            fontSize: '0.74rem',
            padding: '2px 7px',
            borderRadius: '4px',
            fontWeight: 600
          }}
        >
          {node.type}
        </span>

        {/* Node Label / Description */}
        <span className="text-light ms-1" style={{ fontSize: '0.82rem' }}>
          {getNodeLabel(node)}
        </span>

        {/* Location badge */}
        {node.location && (
          <span className="text-secondary ms-2" style={{ fontSize: '0.72rem' }}>
            (L{node.location.line}:C{node.location.column})
          </span>
        )}
      </div>

      {/* Render Children */}
      {hasChildren && expanded && (
        <div className="ast-children">
          {children.map(child => (
            <div key={child.key} className="mt-1">
              <AstTreeNode 
                node={child.node} 
                level={level + 1}
                onSelectNode={onSelectNode}
                selectedNode={selectedNode}
                globalExpanded={globalExpanded}
              />
            </div>
          ))}
        </div>
      )}
    </div>
  );
}

export default function AstViewer({ ast }) {
  const [viewMode, setViewMode] = useState('tree'); // 'tree' or 'json'
  const [selectedNode, setSelectedNode] = useState(null);
  const [globalExpanded, setGlobalExpanded] = useState(null);
  const [copied, setCopied] = useState(false);

  if (!ast) {
    return (
      <div className="p-4 text-center text-secondary">
        <Layers size={36} className="mb-2 opacity-50" />
        <h5>No Abstract Syntax Tree Available</h5>
        <p className="text-muted" style={{ maxWidth: '420px', margin: '0 auto', fontSize: '0.88rem' }}>
          The AST is constructed by the Bison parser when submitted code is syntactically valid. Check the <strong>Diagnostics</strong> tab if your program contained syntax or lexical errors.
        </p>
      </div>
    );
  }

  const jsonString = JSON.stringify(ast, null, 2);

  const handleCopyJson = () => {
    navigator.clipboard.writeText(jsonString);
    setCopied(true);
    setTimeout(() => setCopied(false), 2000);
  };

  return (
    <div className="p-3 h-100 d-flex flex-column">
      {/* AST Toolbar */}
      <div className="d-flex flex-wrap align-items-center justify-content-between gap-2 mb-3">
        <div className="d-flex align-items-center gap-2">
          {/* View mode toggle */}
          <div className="btn-group btn-group-sm">
            <button 
              className={`btn ${viewMode === 'tree' ? 'btn-primary' : 'btn-outline-secondary text-light'}`}
              onClick={() => setViewMode('tree')}
            >
              <Layers size={14} className="me-1" />
              Interactive Tree
            </button>
            <button 
              className={`btn ${viewMode === 'json' ? 'btn-primary' : 'btn-outline-secondary text-light'}`}
              onClick={() => setViewMode('json')}
            >
              <Code size={14} className="me-1" />
              Raw JSON
            </button>
          </div>

          {viewMode === 'tree' && (
            <div className="btn-group btn-group-sm ms-2">
              <button 
                className="btn btn-outline-secondary btn-sm text-light"
                onClick={() => setGlobalExpanded(true)}
                title="Expand All Nodes"
              >
                <Maximize2 size={13} className="me-1" />
                Expand All
              </button>
              <button 
                className="btn btn-outline-secondary btn-sm text-light"
                onClick={() => setGlobalExpanded(false)}
                title="Collapse All Nodes"
              >
                <Minimize2 size={13} className="me-1" />
                Collapse All
              </button>
            </div>
          )}
        </div>

        {/* Copy JSON Button */}
        <button 
          className="btn btn-outline-secondary btn-sm text-light d-flex align-items-center gap-1.5"
          onClick={handleCopyJson}
          title="Copy AST JSON to clipboard"
        >
          {copied ? <Check size={14} className="text-success" /> : <Copy size={14} />}
          <span>{copied ? 'Copied AST' : 'Copy JSON'}</span>
        </button>
      </div>

      {/* Main View Area */}
      <div className="flex-grow-1 overflow-hidden d-flex gap-3" style={{ minHeight: '350px' }}>
        {viewMode === 'tree' ? (
          <>
            {/* Tree hierarchy column */}
            <div 
              className="flex-grow-1 p-3 rounded bg-dark border border-secondary-subtle overflow-auto ast-tree"
              style={{ maxHeight: 'calc(100vh - 280px)' }}
            >
              <AstTreeNode 
                node={ast} 
                onSelectNode={(n) => setSelectedNode(n)} 
                selectedNode={selectedNode}
                globalExpanded={globalExpanded}
              />
            </div>

            {/* Selected Node Details Drawer */}
            {selectedNode && (
              <div 
                className="p-3 rounded bg-dark border border-secondary-subtle d-flex flex-column"
                style={{ width: '300px', maxHeight: 'calc(100vh - 280px)', overflowY: 'auto' }}
              >
                <div className="d-flex align-items-center justify-content-between mb-2 pb-2 border-bottom border-secondary">
                  <div className="d-flex align-items-center gap-1.5 text-info">
                    <Compass size={15} />
                    <strong style={{ fontSize: '0.85rem' }}>Node Inspector</strong>
                  </div>
                  <button 
                    className="btn btn-sm btn-link text-secondary p-0 text-decoration-none"
                    onClick={() => setSelectedNode(null)}
                  >
                    Close
                  </button>
                </div>

                <div className="mb-2">
                  <div className="text-secondary" style={{ fontSize: '0.72rem' }}>Node Type</div>
                  <div className="fw-bold text-light" style={{ fontSize: '0.9rem' }}>{selectedNode.type}</div>
                </div>

                {selectedNode.location && (
                  <div className="mb-2">
                    <div className="text-secondary" style={{ fontSize: '0.72rem' }}>Source Location</div>
                    <code className="text-info" style={{ fontSize: '0.8rem' }}>
                      Line {selectedNode.location.line}, Column {selectedNode.location.column}
                    </code>
                  </div>
                )}

                <div className="mt-2 flex-grow-1">
                  <div className="text-secondary mb-1" style={{ fontSize: '0.72rem' }}>Subtree JSON Snippet</div>
                  <pre 
                    className="p-2 rounded bg-black text-light border border-secondary"
                    style={{ fontSize: '0.75rem', maxHeight: '200px', overflow: 'auto' }}
                  >
                    {JSON.stringify(selectedNode, null, 2)}
                  </pre>
                </div>
              </div>
            )}
          </>
        ) : (
          /* Raw JSON view */
          <div className="w-100 h-100 p-2 rounded bg-black border border-secondary overflow-auto">
            <pre className="text-light m-0 font-monospace" style={{ fontSize: '0.82rem' }}>
              {jsonString}
            </pre>
          </div>
        )}
      </div>
    </div>
  );
}

