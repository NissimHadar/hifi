if exist build-UWP goto dirOK
mkdir build-UWP
:dirOK
cd build-UWP
cmake .. -G "Visual Studio 15 Win64" -DUWP=TRUE
cd ..
