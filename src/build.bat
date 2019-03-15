@echo off

call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat" x86

pushd ..\build\

cl -FC -Zi -nologo ..\src\dtb_test.cpp

popd