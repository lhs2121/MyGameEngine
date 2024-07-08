@echo off
set SolutionDir=%~dp0\EngineMediaLib\
set SolutionFile=%SolutionDir%EngineMediaLib.sln

echo Building EngineBaseLib.sln...
call "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsMSBuildCmd.bat" -arch=x64
msbuild "%SolutionFile%" /p:Configuration=Debug /p:Platform=x64

REM Check if MSBuild failed (exit code != 0)
if errorlevel 1 (
    echo Build failed for %SolutionFile%
) else (
    echo Build succeeded for %SolutionFile%
)
