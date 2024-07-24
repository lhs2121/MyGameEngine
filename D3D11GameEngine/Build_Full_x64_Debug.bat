@echo off
echo 순서대로 빌드를 시작합니다.

call build_baselib_x64_debug.bat
call build_medialib_x64_debug.bat
call build_d3d11lib_x64_debug.bat
call build_corelib_x64_debug.bat
call build_gamelib_x64_debug.bat
call build_app_x64_debug.bat

echo 빌드 완료.
