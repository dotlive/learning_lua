echo off

if not exist build mkdir build
pushd build
cmake -G "Visual Studio 14 2015 Win64" ..
IF %ERRORLEVEL% NEQ 0 cmake -G "Visual Studio 15 2017 Win64" ..
popd
cmake --build build --config Debug

pause
