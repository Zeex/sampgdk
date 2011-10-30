@echo off
echo Generating GNU Makefile
premake4 gmake
echo Generating Code::Blocks project
premake4 codeblocks
echo Generating Visual Studio 2005 project
premake4 vs2005
echo Generating Visual Studio 2008 project
premake4 vs2008 
echo Generating Visual Studio 2010 project
premake4 vs2010