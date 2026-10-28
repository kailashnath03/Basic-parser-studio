import React, { useRef } from 'react';
import Editor from '@monaco-editor/react';
import { Play, RotateCcw, Trash2, Upload, Copy, Check, FileCode2, Sparkles } from 'lucide-react';

export default function EditorPanel({
  code,
  setCode,
  onParse,
  onReset,
  onClear,
  loading,
  examples,
  selectedExampleId,
  onSelectExample
}) {
  const [copied, setCopied] = React.useState(false);
  const fileInputRef = useRef(null);

  const handleCopy = () => {
    navigator.clipboard.writeText(code);
    setCopied(true);
    setTimeout(() => setCopied(false), 2000);
  };

  const handleFileUpload = (e) => {
    const file = e.target.files?.[0];
    if (!file) return;

    if (file.size > 200 * 1024) {
      alert('File size exceeds maximum allowed size (200 KB).');
      return;
    }

    const reader = new FileReader();
    reader.onload = (event) => {
      const content = event.target?.result;
      if (typeof content === 'string') {
        setCode(content);
      }
    };
    reader.readAsText(file);
    e.target.value = '';
  };

  const lineCount = (code.match(/\n/g) || []).length + 1;
  const charCount = code.length;

  return (
    <div className="pane-card">
      {/* Pane Toolbar */}
      <div className="pane-header flex-wrap gap-2">
        <div className="d-flex align-items-center gap-2">
          <FileCode2 size={16} className="text-primary" />
          <span className="fw-semibold text-light" style={{ fontSize: '0.88rem' }}>BASIC Source Code</span>
          
          {/* Example Selector Dropdown */}
          <select 
            className="form-select form-select-sm bg-dark text-light border-secondary ms-2"
            style={{ width: 'auto', fontSize: '0.8rem', paddingRight: '28px' }}
            value={selectedExampleId}
            onChange={(e) => onSelectExample(e.target.value)}
          >
            <option value="">-- Load Sample Program --</option>
            {examples.map((ex) => (
              <option key={ex.id} value={ex.id}>
                {ex.name} ({ex.expectedStatus})
              </option>
            ))}
          </select>
        </div>

        {/* Action Buttons */}
        <div className="d-flex align-items-center gap-1.5 ms-auto">
          {/* Hidden file input */}
          <input 
            type="file" 
            ref={fileInputRef} 
            onChange={handleFileUpload} 
            accept=".bas,.txt" 
            style={{ display: 'none' }} 
          />
          
          <button 
            className="btn btn-sm btn-outline-secondary text-light px-2"
            onClick={() => fileInputRef.current?.click()}
            title="Upload BASIC file (.bas)"
          >
            <Upload size={14} />
          </button>

          <button 
            className="btn btn-sm btn-outline-secondary text-light px-2"
            onClick={handleCopy}
            title="Copy code to clipboard"
          >
            {copied ? <Check size={14} className="text-success" /> : <Copy size={14} />}
          </button>

          <button 
            className="btn btn-sm btn-outline-secondary text-light px-2"
            onClick={onReset}
            title="Reset code to current example or default"
          >
            <RotateCcw size={14} />
          </button>

          <button 
            className="btn btn-sm btn-outline-secondary text-light px-2"
            onClick={onClear}
            title="Clear editor"
          >
            <Trash2 size={14} />
          </button>

          {/* Primary Parse Button */}
          <button 
            className="btn btn-sm btn-purple px-3 d-flex align-items-center gap-1.5 ms-2"
            onClick={onParse}
            disabled={loading || !code.trim()}
            title="Parse BASIC program (Ctrl + Enter)"
          >
            {loading ? (
              <>
                <span className="spinner-border spinner-border-sm" role="status"></span>
                <span>Parsing...</span>
              </>
            ) : (
              <>
                <Play size={14} fill="currentColor" />
                <span>Parse</span>
              </>
            )}
          </button>
        </div>
      </div>

      {/* Code Editor */}
      <div className="pane-body">
        <Editor
          height="100%"
          language="vb"
          theme="vs-dark"
          value={code}
          onChange={(val) => setCode(val || '')}
          options={{
            fontFamily: "'Fira Code', Consolas, monospace",
            fontSize: 13,
            lineNumbers: 'on',
            minimap: { enabled: false },
            scrollBeyondLastLine: false,
            automaticLayout: true,
            tabSize: 4,
            insertSpaces: true,
            wordWrap: 'on',
            renderWhitespace: 'selection',
            cursorBlinking: 'smooth',
            smoothScrolling: true,
            padding: { top: 12, bottom: 12 }
          }}
          onMount={(editor, monaco) => {
            // Add Ctrl+Enter shortcut to parse
            editor.addCommand(monaco.KeyMod.CtrlCmd | monaco.KeyCode.Enter, () => {
              onParse();
            });
          }}
        />
      </div>

      {/* Editor Status Bar */}
      <div 
        className="px-3 py-1 d-flex align-items-center justify-content-between text-secondary"
        style={{ backgroundColor: '#0d1322', borderTop: '1px solid var(--border-color)', fontSize: '0.75rem' }}
      >
        <div className="d-flex align-items-center gap-3">
          <span>Lines: <strong className="text-light">{lineCount}</strong></span>
          <span>Chars: <strong className="text-light">{charCount}</strong></span>
          <span>Encoding: <strong className="text-light">UTF-8</strong></span>
        </div>
        <div>
          <span>Press <kbd className="bg-dark text-light border border-secondary px-1 py-0.5 rounded">Ctrl + Enter</kbd> to parse</span>
        </div>
      </div>
    </div>
  );
}

