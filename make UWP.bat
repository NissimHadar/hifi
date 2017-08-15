if exist build-UWP goto dirOK
mkdir build-UWP
:dirOK

REM Use UWP display plugin sources
ren libraries\display-plugins\src src_WIN
ren libraries\display-plugins\src_UWP src

cd build-UWP
cmake .. -G "Visual Studio 15 Win64" -DUWP=TRUE
cd ..

REM Revert to WIN display plugin sources
ren libraries\display-plugins\src src_UWP
ren libraries\display-plugins\src_WIN src

