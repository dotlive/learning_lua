echo off

if not exist build64 mkdir build64
pushd build64
cmake -G "Visual Studio 14 2015 Win64" ../src
IF %ERRORLEVEL% NEQ 0 cmake -G "Visual Studio 15 2017 Win64" ../src
popd
cmake --build build64 --config Debug

pause
