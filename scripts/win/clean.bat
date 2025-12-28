@echo off
setlocal
set ROOT=%~dp0..\..
for %%I in ("%ROOT%") do set ROOT=%%~fI

rmdir /S /Q "%ROOT%\build\_cmake" 2>NUL
rmdir /S /Q "%ROOT%\build\bin" 2>NUL
rmdir /S /Q "%ROOT%\build\lib" 2>NUL
del /Q "%ROOT%\build\compile_commands.json" 2>NUL

echo Cleaned build outputs.
