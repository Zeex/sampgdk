@echo off

set CMAKE_HOME="%ProgramFiles%\CMake 2.8\"
if exist %CMAKE_HOME% ( goto :cmake_found )

set CMAKE_HOME="%ProgramFiles(x86)%\CMake 2.8\"
if exist %CMAKE_HOME% ( goto :cmake_found )

echo Could not find CMake
goto :exit

:cmake_found:
echo Found CMake: %CMAKE_HOME:"=%

call "%CMAKE_HOME:"=%\bin\cmake.exe" ..\..\

:exit:
