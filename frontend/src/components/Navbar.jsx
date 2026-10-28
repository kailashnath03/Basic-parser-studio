import React from 'react';
import { Terminal, Code2, BookOpen, Info, ShieldCheck, AlertCircle, RefreshCw } from 'lucide-react';

export default function Navbar({ health, onOpenGrammar, onOpenAbout, onCheckHealth }) {
  const isOnline = health?.status === 'ok' && health?.parser?.available;

  return (
    <nav className="navbar navbar-expand-lg studio-navbar px-3 py-2">
      <div className="container-fluid px-0">
        {/* Brand */}
        <div className="d-flex align-items-center gap-2">
          <div className="d-flex align-items-center justify-content-center p-2 rounded-2" style={{ background: 'linear-gradient(135deg, #7c3aed, #4f46e5)' }}>
            <Terminal size={20} className="text-white" />
          </div>
          <div>
            <div className="d-flex align-items-center gap-2">
              <span className="fw-bold fs-5 text-white tracking-wide" style={{ letterSpacing: '-0.02em' }}>
                BASIC Parser Studio
              </span>
              <span className="brand-badge">Flex & Bison</span>
            </div>
            <div className="text-secondary" style={{ fontSize: '0.72rem' }}>
              Compiler Design Lab • Syntax & Lexical Analyzer
            </div>
          </div>
        </div>

        {/* Right Action Controls */}
        <div className="d-flex align-items-center gap-2 mt-2 mt-lg-0">
          {/* Health Status Indicator */}
          <div 
            className="d-flex align-items-center gap-2 px-3 py-1 rounded-pill"
            style={{ 
              backgroundColor: isOnline ? 'rgba(16, 185, 129, 0.1)' : 'rgba(244, 63, 94, 0.1)',
              border: `1px solid ${isOnline ? 'rgba(16, 185, 129, 0.3)' : 'rgba(244, 63, 94, 0.3)'}`,
              fontSize: '0.78rem',
              cursor: 'pointer'
            }}
            onClick={onCheckHealth}
            title="Click to re-check parser engine connectivity"
          >
            {isOnline ? (
              <>
                <span className="pulse-online"></span>
                <span className="text-success fw-medium">Parser Engine Online</span>
              </>
            ) : (
              <>
                <AlertCircle size={14} className="text-danger" />
                <span className="text-danger fw-medium">Parser Engine Offline</span>
              </>
            )}
          </div>

          {/* Grammar Reference Button */}
          <button 
            className="btn btn-outline-secondary btn-sm d-flex align-items-center gap-1.5 px-2.5 py-1 text-light border-secondary-subtle"
            onClick={onOpenGrammar}
            title="View Context-Free Grammar Rules"
          >
            <BookOpen size={15} className="text-info" />
            <span>Grammar</span>
          </button>

          {/* About / Architecture Button */}
          <button 
            className="btn btn-outline-secondary btn-sm d-flex align-items-center gap-1.5 px-2.5 py-1 text-light border-secondary-subtle"
            onClick={onOpenAbout}
            title="View Compiler Architecture & Lab Details"
          >
            <Info size={15} className="text-warning" />
            <span>About</span>
          </button>
        </div>
      </div>
    </nav>
  );
}

