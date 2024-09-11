@echo off
echo 순서대로 빌드를 시작합니다.

call 0.Build_BaseLib.bat
call 1.Build_MediaLib.bat
call 2.Build_ResourceLib.bat
call 3.Build_EngineLib.bat
call 4.Build_Gamelib.bat
call 5.Build_Game.bat

echo 빌드 완료.
