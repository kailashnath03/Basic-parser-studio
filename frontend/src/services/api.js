// API Service for BASIC Parser Studio
// Uses VITE_API_URL in production (e.g., on Render), or empty string for local dev with Vite proxy
const RAW_API_URL = import.meta.env.VITE_API_URL || '';
const API_BASE_URL = RAW_API_URL.replace(/\/+$/, '');

export async function checkHealth() {
    try {
        const res = await fetch(`${API_BASE_URL}/api/health`, {
            headers: { 'Accept': 'application/json' }
        });
        if (!res.ok) throw new Error(`HTTP ${res.status}`);
        return await res.json();
    } catch (err) {
        return {
            status: 'offline',
            error: err.message,
            parser: { available: false }
        };
    }
}

export async function getExamples() {
    try {
        const res = await fetch(`${API_BASE_URL}/api/examples`);
        if (!res.ok) throw new Error(`HTTP ${res.status}`);
        const data = await res.json();
        return data.examples || [];
    } catch (err) {
        console.error('Failed to load examples:', err);
        return [];
    }
}

export async function parseBasicCode(code) {
    const res = await fetch(`${API_BASE_URL}/api/parse`, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
            'Accept': 'application/json'
        },
        body: JSON.stringify({ code })
    });

    if (!res.ok) {
        const errorText = await res.text();
        let errorData;
        try {
            errorData = JSON.parse(errorText);
        } catch {
            errorData = { error: errorText || `HTTP ${res.status}` };
        }
        return errorData;
    }

    return await res.json();
}

