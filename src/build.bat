@echo off

call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat" x64

pushd ..\build\

cl -FC -Zi -nologo ..\src\dtb_test.cpp ..\src\dtb_gl.c /link SDL2.lib SDL2main.lib opengl32.lib -SUBSYSTEM:CONSOLE

popd