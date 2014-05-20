@echo off
rmdir build /s /q
mkdir build
cd build
cmake .. -G "Visual Studio 12"
astro.sln