@echo off
setlocal enabledelayedexpansion

set BUILD_TYPE=%~1
if "%BUILD_TYPE%"=="" set BUILD_TYPE=Debug

set TARGET=%~2

set ROOT=%~dp0..\..
for %%I in ("%ROOT%") do set ROOT=%%~fI
set BUILD_DIR=%ROOT%\build\_cmake

if not exist "%BUILD_DIR%\CMakeCache.txt" (
  call "%~dp0configure.bat" %BUILD_TYPE%
  if errorlevel 1 exit /b %ERRORLEVEL%
)

if "%TARGET%"=="" (
  cmake --build "%BUILD_DIR%" --config %BUILD_TYPE%
) else (
  cmake --build "%BUILD_DIR%" --config %BUILD_TYPE% --target %TARGET%
)

exit /b %ERRORLEVEL%
