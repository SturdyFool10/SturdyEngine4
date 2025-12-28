@echo off
setlocal enabledelayedexpansion

set BUILD_TYPE=%~1
if "%BUILD_TYPE%"=="" set BUILD_TYPE=Debug

set ROOT=%~dp0..\..
for %%I in ("%ROOT%") do set ROOT=%%~fI

set BUILD_DIR=%ROOT%\build\_cmake

if not exist "%ROOT%\build" mkdir "%ROOT%\build" >NUL 2>&1
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%" >NUL 2>&1

cmake -S "%ROOT%" -B "%BUILD_DIR%" -G Ninja ^
  -DCMAKE_BUILD_TYPE=%BUILD_TYPE% ^
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

if exist "%BUILD_DIR%\compile_commands.json" (
  copy /Y "%BUILD_DIR%\compile_commands.json" "%ROOT%\build\compile_commands.json" >NUL
)

exit /b %ERRORLEVEL%
