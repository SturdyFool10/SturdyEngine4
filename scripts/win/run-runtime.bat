@echo off
setlocal

set BUILD_TYPE=%~1
if "%BUILD_TYPE%"=="" set BUILD_TYPE=Debug

set ROOT=%~dp0..\..
for %%I in ("%ROOT%") do set ROOT=%%~fI

call "%~dp0build.bat" %BUILD_TYPE% runtime
if errorlevel 1 exit /b %ERRORLEVEL%

set EXE=%ROOT%\build\bin\runtime.exe
if not exist "%EXE%" (
  echo Expected runtime exe not found: "%EXE%"
  exit /b 1
)

"%EXE%"
