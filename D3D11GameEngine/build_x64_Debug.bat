@echo off
setlocal

set "ROOT=%~dp0"
set "VS_MSBUILD_CMD=C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsMSBuildCmd.bat"

if not exist "%VS_MSBUILD_CMD%" (
    echo Visual Studio build environment was not found:
    echo %VS_MSBUILD_CMD%
    pause
    exit /b 1
)

call "%VS_MSBUILD_CMD%" -arch=x64
if errorlevel 1 (
    echo Failed to initialize Visual Studio build environment.
    pause
    exit /b 1
)

call :BuildProject "BaseLibrary" "%ROOT%BaseLibrary\BaseLibrary.sln"
if errorlevel 1 goto :BuildFailed

call :BuildProject "InputLibrary" "%ROOT%InputLibrary\InputLibrary.sln"
if errorlevel 1 goto :BuildFailed

call :BuildProject "WindowLibrary" "%ROOT%WindowLibrary\WindowLibrary.sln"
if errorlevel 1 goto :BuildFailed

call :BuildProject "RendererLibrary" "%ROOT%RendererLibrary\RendererLibrary.sln"
if errorlevel 1 goto :BuildFailed

call :BuildProject "CollisionLibrary" "%ROOT%CollisionLibrary\CollisionLibrary.sln"
if errorlevel 1 goto :BuildFailed

call :BuildProject "D3D11Game" "%ROOT%GameLibrary\GameLibrary.sln"
if errorlevel 1 goto :BuildFailed

echo.
echo Build succeeded.
pause
exit /b 0

:BuildProject
echo.
echo ============================================================
echo Building %~1
echo %~2
echo ============================================================

if not exist "%~2" (
    echo Missing project or solution: %~2
    exit /b 1
)

msbuild "%~2" /p:Configuration=Debug /p:Platform=x64 /m /v:minimal
if errorlevel 1 (
    echo.
    echo Build failed: %~1
    exit /b 1
)

echo Build succeeded: %~1
exit /b 0

:BuildFailed
echo.
echo Build stopped because an error occurred above.
pause
exit /b 1
