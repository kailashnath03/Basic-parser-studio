import React, { useState, useEffect } from 'react';
import Navbar from './components/Navbar';
import EditorPanel from './components/EditorPanel';
import StatsBanner from './components/StatsBanner';
import TokensTab from './components/TokensTab';
import AstViewer from './components/AstViewer';
import DiagnosticsTab from './components/DiagnosticsTab';
import GrammarTab from './components/GrammarTab';
import AboutModal from './components/AboutModal';
import { checkHealth, getExamples, parseBasicCode } from './services/api';
import { Hash, Layers, AlertCircle, BookOpen } from 'lucide-react';

const DEFAULT_CODE = `REM Welcome to BASIC Parser Studio!
REM Compiler Design Lab - Syntax & Lexical Analyzer

LET A = 10
B = 20
RESULT = 2 + 3 * 4 ^ 2

IF RESULT > 50 THEN
    PRINT "High Value Calculation: "; RESULT
ELSE
    PRINT "Standard Value: "; RESULT
END IF

FOR I = 1 TO 3
    PRINT "Loop Step: "; I
NEXT I
`;

export default function App() {
  const [code, setCode] = useState(DEFAULT_CODE);
  const [health, setHealth] = useState(null);
  const [examples, setExamples] = useState([]);
  const [selectedExampleId, setSelectedExampleId] = useState('');
  const [activeTab, setActiveTab] = useState('ast');
  const [parseResult, setParseResult] = useState(null);
  const [loading, setLoading] = useState(false);
  const [showAboutModal, setShowAboutModal] = useState(false);

  // Initialize: Check backend health and load examples
  useEffect(() => {
    async function init() {
      const h = await checkHealth();
      setHealth(h);

      const exs = await getExamples();
      setExamples(exs);

      // Perform initial parse
      handleParseCode(DEFAULT_CODE);
    }
    init();
  }, []);

  const handleParseCode = async (sourceToParse = code) => {
    if (!sourceToParse.trim()) return;
    setLoading(true);

    try {
      const result = await parseBasicCode(sourceToParse);
      setParseResult(result);

      // If errors were returned, auto-switch to Diagnostics tab so user notices
      if (result.success === false && result.diagnostics && result.diagnostics.length > 0) {
        setActiveTab('diagnostics');
      } else if (activeTab === 'diagnostics' && result.success === true) {
        setActiveTab('ast');
      }
    } catch (err) {
      console.error('Parse error:', err);
      setParseResult({
        success: false,
        status: 'NETWORK_ERROR',
        tokens: [],
        ast: null,
        diagnostics: [{
          type: 'CONNECTION_ERROR',
          message: `Cannot reach backend API: ${err.message}`,
          line: 1,
          column: 1,
          snippet: ''
        }],
        statistics: { tokenCount: 0, errorCount: 1, lineCount: 0, parseStatus: 'NETWORK_ERROR' },
        executionTimeMs: 0
      });
      setActiveTab('diagnostics');
    } finally {
      setLoading(false);
    }
  };

  const handleSelectExample = (id) => {
    setSelectedExampleId(id);
    const found = examples.find(ex => ex.id === id);
    if (found) {
      setCode(found.code);
      handleParseCode(found.code);
    }
  };

  const handleReset = () => {
    if (selectedExampleId) {
      const found = examples.find(ex => ex.id === selectedExampleId);
      if (found) {
        setCode(found.code);
        handleParseCode(found.code);
        return;
      }
    }
    setCode(DEFAULT_CODE);
    handleParseCode(DEFAULT_CODE);
  };

  const handleClear = () => {
    setCode('');
    setParseResult(null);
  };

  const refreshHealth = async () => {
    const h = await checkHealth();
    setHealth(h);
  };

  const errorCount = parseResult?.diagnostics?.length || 0;
  const tokenCount = parseResult?.tokens?.length || 0;

  return (
    <div className="d-flex flex-column vh-100 bg-dark text-light overflow-hidden">
      {/* Top Navigation Bar */}
      <Navbar 
        health={health}
        onOpenGrammar={() => setActiveTab('grammar')}
        onOpenAbout={() => setShowAboutModal(true)}
        onCheckHealth={refreshHealth}
      />

      {/* Main Workbench Body */}
      <div className="container-fluid flex-grow-1 px-3 py-2 overflow-hidden">
        <div className="row g-2 h-100">
          {/* Left Column: Code Editor */}
          <div className="col-12 col-lg-5 h-100">
            <EditorPanel 
              code={code}
              setCode={setCode}
              onParse={() => handleParseCode(code)}
              onReset={handleReset}
              onClear={handleClear}
              loading={loading}
              examples={examples}
              selectedExampleId={selectedExampleId}
              onSelectExample={handleSelectExample}
            />
          </div>

          {/* Right Column: Parser Results Studio */}
          <div className="col-12 col-lg-7 h-100">
            <div className="pane-card">
              {/* Parse Status & Statistics Banner */}
              <StatsBanner result={parseResult} loading={loading} />

              {/* Result Navigation Tabs */}
              <div className="pane-header p-0">
                <ul className="nav nav-tabs nav-tabs-custom w-100 px-3">
                  <li className="nav-item">
                    <button 
                      className={`nav-link ${activeTab === 'ast' ? 'active' : ''}`}
                      onClick={() => setActiveTab('ast')}
                    >
                      <Layers size={15} />
                      <span>Abstract Syntax Tree</span>
                    </button>
                  </li>

                  <li className="nav-item">
                    <button 
                      className={`nav-link ${activeTab === 'tokens' ? 'active' : ''}`}
                      onClick={() => setActiveTab('tokens')}
                    >
                      <Hash size={15} />
                      <span>Tokens</span>
                      {tokenCount > 0 && (
                        <span className="badge bg-secondary rounded-pill" style={{ fontSize: '0.68rem' }}>
                          {tokenCount}
                        </span>
                      )}
                    </button>
                  </li>

                  <li className="nav-item">
                    <button 
                      className={`nav-link ${activeTab === 'diagnostics' ? 'active' : ''}`}
                      onClick={() => setActiveTab('diagnostics')}
                    >
                      <AlertCircle size={15} />
                      <span>Diagnostics</span>
                      {errorCount > 0 && (
                        <span className="badge bg-danger rounded-pill" style={{ fontSize: '0.68rem' }}>
                          {errorCount}
                        </span>
                      )}
                    </button>
                  </li>

                  <li className="nav-item ms-auto">
                    <button 
                      className={`nav-link ${activeTab === 'grammar' ? 'active' : ''}`}
                      onClick={() => setActiveTab('grammar')}
                    >
                      <BookOpen size={15} />
                      <span>Grammar Reference</span>
                    </button>
                  </li>
                </ul>
              </div>

              {/* Tab Contents */}
              <div className="pane-body p-0">
                {activeTab === 'ast' && <AstViewer ast={parseResult?.ast} />}
                {activeTab === 'tokens' && <TokensTab tokens={parseResult?.tokens} />}
                {activeTab === 'diagnostics' && (
                  <DiagnosticsTab 
                    diagnostics={parseResult?.diagnostics} 
                    isSuccess={parseResult?.success}
                  />
                )}
                {activeTab === 'grammar' && <GrammarTab />}
              </div>
            </div>
          </div>
        </div>
      </div>

      {/* About & Lab Info Modal */}
      <AboutModal 
        isOpen={showAboutModal}
        onClose={() => setShowAboutModal(false)}
      />
    </div>
  );
}

