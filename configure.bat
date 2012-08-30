@echo off

if NOT "%CMAKE%" == "" (
	goto CMakeFound
)

set CMAKE_VER=2.8
set CMAKE_PATH=%ProgramFiles%\CMake %CMAKE_VER%\bin

if NOT EXIST "%CMAKE_PATH%" (
	set CMAKE_PATH=
)

set CMAKE=%CMAKE_PATH%\cmake.exe

if NOT EXIST "%CMAKE%" (
	echo Could not find CMake
	goto Exit
)

:CMakeFound
echo Found CMake executable: %CMAKE%

if NOT EXIST "build\windows" (
	mkdir "build\windows"
)

cd build\windows
"%CMAKE%" ..\..\ %*

echo Now it's time to compile!
goto Exit

:Exit
exit
