@echo off

setlocal
set PROJECT_PATH=vs.proj\ViNpp.vcxproj
set FILE_NAME=ViNpp.dll
REM Notepad++ plugin must be placed in folder with the same name
set OUTPUT_DIR=C:\Program Files\Notepad++\plugins\ViNpp

REM MSBuild configuration and platform
set CONFIGURATION=Release
set PLATFORM=x64

REM Verify MSBuild is available
where msbuild >nul 2>nul
if %errorlevel% neq 0 (
    echo MSBuild not found. Ensure it is installed and available in PATH.
    exit /b 1
)

REM Determine the build output directory
if /i "%PLATFORM%"=="x64" (
    set BUILD_OUTPUT_DIR="bin64"
) else if /i "%PLATFORM%"=="win32" (
    set BUILD_OUTPUT_DIR="bin"
) else if /i "%PLATFORM%"=="arm64" (
    set BUILD_OUTPUT_DIR="arm64"
) else (
    echo Unsupported platform: %PLATFORM%
    exit /b 1
)

REM Run MSBuild
msbuild %PROJECT_PATH% /p:Configuration=%CONFIGURATION% /p:Platform=%PLATFORM%
if %errorlevel% neq 0 (
    echo MSBuild failed.
    exit /b 1
)

REM Copy to output directory
if not exist "%OUTPUT_DIR%" (
    mkdir "%OUTPUT_DIR%"
)
set SOURCE_FILE="%BUILD_OUTPUT_DIR%\%FILE_NAME%"
copy /Y "%SOURCE_FILE%" "%OUTPUT_DIR%\%FILE_NAME%"
if %errorlevel% neq 0 (
    echo Failed to copy file to output directory.
    exit /b 1
)

echo Build and copy operation completed successfully.
endlocal
