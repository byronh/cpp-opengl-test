@echo off
rmdir build /s /q
mkdir build
cd build
cmake .. -G "Visual Studio 12 Win64"
astro.sln