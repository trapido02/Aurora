@echo off
pushd ..
premake\windows\premake5.exe --file=premake5.lua vs2022
popd
pause