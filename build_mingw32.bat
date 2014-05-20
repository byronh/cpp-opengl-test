@echo off
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
cd ..
echo Press any key to continue...
pause > nul