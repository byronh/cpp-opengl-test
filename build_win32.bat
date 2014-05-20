@echo off
mkdir build
cd build
cmake .. -G "Visual Studio 12"
astro.sln
cd ..