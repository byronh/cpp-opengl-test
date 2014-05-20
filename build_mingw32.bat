@echo off
rmdir build /s /q
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
echo Press any key to continue...
pause > nul