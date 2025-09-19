@echo off
REM ================================
REM Build and Run Course Management
REM ================================

REM Set source and output names
set SRC=main.cpp
set OUT=cms_cpp.exe

echo Compiling %SRC% ...
g++ -std=c++11 -O2 -o %OUT% %SRC%

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo Compilation failed. Fix errors above.
    pause
    exit /b
)

echo.
echo Build successful! Running program...
echo =====================================

%OUT%

echo.
pause
