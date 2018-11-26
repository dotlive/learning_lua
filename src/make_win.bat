echo off

mkdir build32 & pushd build32
cmake -G "Visual Studio 14 2015" ..
IF %ERRORLEVEL% NEQ 0 cmake -G "Visual Studio 15 2017" ..
popd
cmake --build build32 --config Debug

mkdir build64 & pushd build64
cmake -G "Visual Studio 14 2015 Win64" ..
IF %ERRORLEVEL% NEQ 0 cmake -G "Visual Studio 15 2017 Win64" ..
popd
cmake --build build64 --config Debug

pause
