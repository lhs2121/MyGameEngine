@echo off
echo 순서대로 빌드를 시작합니다.

call build_x64_Debug_BaseLibrary
call build_x64_Debug_RendererLibrary
call build_x64_Debug_CollisionLibrary
call build_x64_Debug_EngineLibrary
call build_x64_Debug_GameLibrary
call build_x64_Debug_Game

echo 빌드 완료.