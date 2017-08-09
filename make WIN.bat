if exist build-WIN goto OK
mkdir build-WIN
:dirOK
cd build-WIN
cmake .. -G "Visual Studio 15 Win64"
cd ..
