@echo off
echo ====================================================
echo   Launching BASIC Parser Studio (Backend + Frontend)
echo ====================================================
start "BASIC Parser Backend" cmd /c "cd backend && npm start"
timeout /t 2 /nobreak >nul
start "BASIC Parser Frontend" cmd /c "cd frontend && npm run dev"
echo Services launched!
echo Backend:  http://localhost:5000
echo Frontend: http://localhost:3000

