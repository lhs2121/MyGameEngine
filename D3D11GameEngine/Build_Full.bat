@echo off
echo 순서대로 빌드를 시작합니다.

call Build_BaseLib.bat
call Build_MediaLib.bat
call Build_D3D11Lib.bat
call Build_EngineLib.bat
call Build_Gamelib.bat
call Build_Game.bat

echo 빌드 완료.
