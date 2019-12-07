@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars64.bat"
set build=build_msvc15_win64
if not exist %build% mkdir %build%
cd %build%
cmake -G "Visual Studio 15 2017 Win64" -DCMAKE_PREFIX_PATH="D:\\Qt\\5.12.0\\msvc2017_64\\lib\\cmake" ..
pause