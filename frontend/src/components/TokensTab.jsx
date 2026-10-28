import React, { useState, useMemo } from 'react';
import { Search, Filter, Download, Hash } from 'lucide-react';

export default function TokensTab({ tokens }) {
  const [searchTerm, setSearchTerm] = useState('');
  const [categoryFilter, setCategoryFilter] = useState('ALL');

  const getBadgeClass = (type) => {
    if (type.startsWith('KEYWORD_')) return 'badge-keyword';
    if (type === 'IDENTIFIER') return 'badge-ident';
    if (type.includes('LITERAL')) return 'badge-literal';
    if (['PLUS', 'MINUS', 'MULTIPLY', 'DIVIDE', 'INTDIV', 'POWER', 'EQUALS', 'NOT_EQUALS', 'LESS_THAN', 'GREATER_THAN', 'LESS_EQUALS', 'GREATER_EQUALS'].includes(type)) return 'badge-operator';
    if (['EOL', 'COLON', 'SEMICOLON', 'COMMA', 'LPAREN', 'RPAREN'].includes(type)) return 'badge-delimiter';
    if (type === 'COMMENT') return 'badge-comment';
    return 'badge-delimiter';
  };

  const getCategory = (type) => {
    if (type.startsWith('KEYWORD_')) return 'KEYWORDS';
    if (type === 'IDENTIFIER') return 'IDENTIFIERS';
    if (type.includes('LITERAL')) return 'LITERALS';
    if (['PLUS', 'MINUS', 'MULTIPLY', 'DIVIDE', 'INTDIV', 'POWER', 'EQUALS', 'NOT_EQUALS', 'LESS_THAN', 'GREATER_THAN', 'LESS_EQUALS', 'GREATER_EQUALS'].includes(type)) return 'OPERATORS';
    if (['EOL', 'COLON', 'SEMICOLON', 'COMMA', 'LPAREN', 'RPAREN'].includes(type)) return 'DELIMITERS';
    if (type === 'COMMENT') return 'COMMENTS';
    return 'OTHER';
  };

  const filteredTokens = useMemo(() => {
    if (!tokens || !Array.isArray(tokens)) return [];
    return tokens.filter((tok, idx) => {
      const cat = getCategory(tok.type);
      if (categoryFilter !== 'ALL' && cat !== categoryFilter) return false;
      if (searchTerm.trim()) {
        const q = searchTerm.toLowerCase();
        const matchesType = tok.type.toLowerCase().includes(q);
        const matchesLex = tok.lexeme.toLowerCase().includes(q);
        const matchesIdx = (idx + 1).toString() === q;
        return matchesType || matchesLex || matchesIdx;
      }
      return true;
    });
  }, [tokens, categoryFilter, searchTerm]);

  const handleExportCSV = () => {
    if (!tokens || tokens.length === 0) return;
    const headers = ['Index', 'Token Type', 'Lexeme', 'Line', 'Column'];
    const rows = tokens.map((t, i) => [
      i + 1,
      `"${t.type}"`,
      `"${t.lexeme.replace(/"/g, '""')}"`,
      t.line,
      t.column
    ]);
    const csvContent = [headers.join(','), ...rows.map(r => r.join(','))].join('\n');
    const blob = new Blob([csvContent], { type: 'text/csv' });
    const url = URL.createObjectURL(blob);
    const a = document.createElement('a');
    a.href = url;
    a.download = 'basic_tokens.csv';
    a.click();
    URL.revokeObjectURL(url);
  };

  if (!tokens || tokens.length === 0) {
    return (
      <div className="p-4 text-center text-secondary">
        <Hash size={32} className="mb-2 opacity-50" />
        <p>No tokens recorded yet. Write BASIC code and click <strong>Parse</strong>.</p>
      </div>
    );
  }

  const categories = ['ALL', 'KEYWORDS', 'IDENTIFIERS', 'LITERALS', 'OPERATORS', 'DELIMITERS', 'COMMENTS'];

  return (
    <div className="p-3 h-100 d-flex flex-direction-column flex-column">
      {/* Controls Bar */}
      <div className="d-flex flex-wrap align-items-center justify-content-between gap-2 mb-3">
        {/* Search Input */}
        <div className="input-group input-group-sm" style={{ maxWidth: '280px' }}>
          <span className="input-group-text bg-dark border-secondary text-secondary">
            <Search size={14} />
          </span>
          <input
            type="text"
            className="form-control bg-dark border-secondary text-light"
            placeholder="Search lexeme or type..."
            value={searchTerm}
            onChange={(e) => setSearchTerm(e.target.value)}
          />
        </div>

        {/* Category Pills */}
        <div className="btn-group btn-group-sm flex-wrap">
          {categories.map((cat) => (
            <button
              key={cat}
              className={`btn btn-sm ${categoryFilter === cat ? 'btn-primary' : 'btn-outline-secondary text-light border-secondary'}`}
              onClick={() => setCategoryFilter(cat)}
              style={{ fontSize: '0.75rem', padding: '2px 8px' }}
            >
              {cat}
            </button>
          ))}
        </div>

        {/* Export Button */}
        <button 
          className="btn btn-outline-secondary btn-sm text-light border-secondary d-flex align-items-center gap-1.5"
          onClick={handleExportCSV}
          title="Export tokens to CSV"
        >
          <Download size={13} />
          <span>Export CSV</span>
        </button>
      </div>

      {/* Token Count Indicator */}
      <div className="text-secondary mb-2" style={{ fontSize: '0.78rem' }}>
        Showing <strong>{filteredTokens.length}</strong> of <strong>{tokens.length}</strong> total tokens
      </div>

      {/* Table Container */}
      <div className="table-responsive flex-grow-1" style={{ maxHeight: 'calc(100vh - 270px)' }}>
        <table className="table table-dark table-hover table-striped token-table mb-0 align-middle">
          <thead>
            <tr>
              <th style={{ width: '60px' }}>#</th>
              <th>Token Type</th>
              <th>Lexeme</th>
              <th style={{ width: '80px' }}>Line</th>
              <th style={{ width: '80px' }}>Col</th>
            </tr>
          </thead>
          <tbody>
            {filteredTokens.length > 0 ? (
              filteredTokens.map((t, idx) => (
                <tr key={idx}>
                  <td className="text-secondary">{idx + 1}</td>
                  <td>
                    <span className={`token-badge ${getBadgeClass(t.type)}`}>
                      {t.type}
                    </span>
                  </td>
                  <td>
                    <code className="text-light px-1 py-0.5 rounded bg-dark border border-secondary" style={{ fontSize: '0.85rem' }}>
                      {t.lexeme === '\n' ? '\\n' : t.lexeme}
                    </code>
                  </td>
                  <td className="text-info">{t.line}</td>
                  <td className="text-secondary">{t.column}</td>
                </tr>
              ))
            ) : (
              <tr>
                <td colSpan="5" className="text-center text-secondary py-4">
                  No tokens matching filter "{searchTerm || categoryFilter}".
                </td>
              </tr>
            )}
          </tbody>
        </table>
      </div>
    </div>
  );
}

