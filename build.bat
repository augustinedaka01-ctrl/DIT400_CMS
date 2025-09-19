@echo off
REM ================================
REM Build and Run Course Management (Java)
REM ================================

REM Source and output names
set SRC=Main.java
set CLASS=Main.class
set JAR=cms_java.jar

echo Compiling %SRC% ...
javac %SRC%

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo Compilation failed. Fix errors above.
    pause
    exit /b
)

echo.
echo Creating JAR file %JAR% ...
echo Main-Class: Main > manifest.txt
jar cfm %JAR% manifest.txt %CLASS%

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo JAR creation failed.
    pause
    exit /b
)

echo.
echo Build successful! Running program...
echo =====================================
java -jar %JAR%

echo.
pause
