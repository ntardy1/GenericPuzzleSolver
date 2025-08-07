@echo off

REM Create build directory if it doesn't already exist
if exist ".\build\" (
    echo build directory exists
) else (
    mkdir build
)

cd .\build\
cmake -G "MinGW Makefiles" ..
cmake --build .