@echo off
echo 순서대로 빌드를 시작합니다.

call Build_Base_x64_Debug.bat
call Build_Media_x64_Debug.bat
call Build_D3D11_x64_Debug.bat
call Build_Game_x64_Debug.bat

echo 빌드 완료.
