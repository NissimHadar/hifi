if exist build-UWP goto dirOK
mkdir build-UWP
:dirOK

REM Use UWP display plugin sources
ren libraries\display-plugins\src src_WIN
ren libraries\display-plugins\src_UWP src

REM Sleep 2 seconds - the renaming seems to take some time
ping -n 3 127.0.0.1 > NUL

cd build-UWP
cmake .. -G "Visual Studio 15 Win64" -DUWP=TRUE
cd ..

REM Revert to WIN display plugin sources
ren libraries\display-plugins\src src_UWP
ren libraries\display-plugins\src_WIN src

