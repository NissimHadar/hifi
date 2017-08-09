if exist build-WIN goto dirOK
mkdir build-WIN
:dirOK
cd build-WIN
cmake .. -G "Visual Studio 15 Win64"
cd ..
