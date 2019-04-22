# General
This document describes the process to build Qt 5.12.3.  
Note that there are two patches.  The first (to qfloat16.h) is needed to compiel QT 5.12.3 on Visual Studio 2017 due to a bug in Visual Studio (*bitset* will not compile.  Note that there is a change in CMakeLists.txt to support this.  
The second patch is to OpenSL ES audio.
## Requirements
### Windows
1.  Visual Studio 2017  
    If you don’t have Community or Professional edition of Visual Studio 2017, download [Visual Studio Community 2017](https://www.visualstudio.com/downloads/).  
Install with defaults

1.  python 2.7.16  
Check if needed running `python --version` - should return python 2.7.x  
Install from https://www.python.org/ftp/python/2.7.16/python-2.7.16.amd64.msi  
Add path to python executable to PATH.  

NOTE:  REMOVE python 3 from PATH.  Our regular build uses python 3.  This will still work, because HIFI_PYTHON_EXEC points to the python 3 executable.

Verify that python runs python 2.7 (run “python --version”)  
1.  git >= 1.6  
Check if needed `git --version`  
Download from https://git-scm.com/download/win  
Verify by entering `git --version`
1.  perl >= 5.14  
Install from Strawberry Perl - http://strawberryperl.com/ - 5.28.1.1 64 bit to C:\Strawberry\  
Verify by running `perl --version`
1.  flex and bison  
Download from https://sourceforge.net/projects/winflexbison/files/latest/download  
Uncompress in C:\flex_bison  
Rename win-bison.exe to bison.exe and win-flex.exe to flex.exe  
Add C:\flex_bison to PATH  
Verify by running `flex --version`  
Verify by running `bison --version`
1.  gperf  
Install from http://gnuwin32.sourceforge.net/downlinks/gperf.php  
Install  
Add C:\Program Files (x86)\GnuWin32\bin to PATH  
Verify by running `gperf --version`
### Linux
Tested on Ubuntu 18.04  
1.  qt5 requirements  
edit /etc/apt/sources.list (edit as root)  
replace all *# deb-src* with *deb-src* (in vi `1,$s/# deb-src/deb-src/`)  
`sudo apt-get update -y`  
`sudo apt-get upgrade -y`  
`sudo apt-get build-dep qt5-default -y`
1.  git >= 1.6  
Check if needed `git --version`
`sudo apt-get install git -y`  
Verify again
1.  python   
Check if needed `python --version` - should return python 2.7.x
`sudo apt-get install python -y` (not python 3!)  
Verify again
1.  gperf  
Check if needed `gperf --version`
`sudo apt-get install gperf -y`  
Verify again
1.  bison and flex  
Check if needed `flex --version`  and `bison --version`  
`sudo apt-get install flex bison -y`  
Verify again
1.  pkg-config (needed for qtwebengine)  
Check if needed `pkg-config --version`  
`sudo apt-get install pkg-config -y`
Verify again
1.  OpenGL  
Verify (first install mesa-utils - `sudo apt install mesa-utils -y`) by `glxinfo | grep "OpenGL version"`
`sudo apt-get install libgl1-mesa-dev -y`  
`sudo ln -s /usr/lib/x86_64-linux-gnu/libGL.so.346.35 /usr/lib/x86_64-linux-gnu/libGL.so.1.2.0`  
Verify again 
1.  make  
Check if needed `make --version`
`sudo apt-get install make -y`  
Verify again  
1.  g++  
Check if needed  
 `g++ --version`
`sudo apt-get install g++ -y`
Verify again
1.  dbus-1 (needed for qtwebengine)  
`sudo apt-get install libdbus-glib-1-dev -y`  
1.  nss (needed for qtwebengine)  
`sudo apt-get install libnss3-dev -y`
### Mac
1.  git >= 1.6  
Check if needed `git --version`  
Install from https://git-scm.com/download/mac  
Verify again
1.  pkg-config  
brew fontconfig dbus-glib stall pkg-config
1.  dbus-1  
brew install dbus-glib
## Build Process
### General
qt is cloned to the qt5 folder.  
The build is performed in the qt5-build folder.  
Build products are installed to the qt5-install folder.  
Before running configure, make sure that the qt5-build folder is empty.

**Only run the patches once!!!**
### Windows
Before building, verify that **HIFI_VCPKG_BASE_VERSION** points to a *vcpkg* folder containing *packages\openssl-windows_x64-windows*. If not, follow https://github.com/highfidelity/vcpkg to install *vcpkg* and then *openssl*.   

git clone --recursive https://code.qt.io/qt/qt5.git -b 5.12.3 --single-branch

*  Copy the **patches** folder to qt5  
*  Copy the **qt5vars.bat** file to qt5  
*  Apply the two patches to Qt  
cd qt5  
git apply --ignore-space-change --ignore-whitespace patches/qfloat16.patch
git apply --ignore-space-change --ignore-whitespace patches/aec.patch  

cd ..  
mkdir qt5-install  
mkdir qt5-build  
cd qt5-build

run ..\qt5\qt5vars.bat  
cd ..\..\qt5-build  

..\qt5\configure -opensource -confirm-license -opengl desktop -platform win32-msvc -openssl-linked  OPENSSL_LIBS="-lssleay32 -llibeay32"  -I %HIFI_VCPKG_BASE_VERSION%\packages\openssl-windows_x64-windows\include -L %HIFI_VCPKG_BASE_VERSION%\packages\openssl-windows_x64-windows\lib -nomake examples -nomake tests -skip qttranslations -skip qtserialport -skip qt3d -skip qtlocation -skip qtwayland -skip qtsensors -skip qtgamepad -skip qtspeech -skip qtcharts -skip qtx11extras -skip qtmacextras -skip qtvirtualkeyboard -skip qtpurchasing -skip qtdatavis3d -no-warnings-are-errors -no-pch -prefix ..\qt5-install

nmake  
nmake install
### Linux
git clone --recursive git://code.qt.io/qt/qt5.git -b 5.12.3 --single-branch

*  Copy the **patches** folder to qt5  
*   Apply the two patches to Qt  
cd qt5  
git apply --ignore-space-change --ignore-whitespace patches/aec.patch  
cd ..

mkdir qt5-install  
mkdir qt5-build  
cd qt5-build

../qt5/configure -opensource -confirm-license -platform linux-g++-64 -nomake examples -nomake tests -skip qttranslations -skip qtserialport -skip qt3d -skip qtlocation -skip qtwayland -skip qtsensors -skip qtgamepad -skip qtspeech -skip qtcharts -skip qtx11extras -skip qtmacextras -skip qtvirtualkeyboard -skip qtpurchasing -skip qtdatavis3d -no-warnings-are-errors -no-pch -prefix ../qt5-install

make  
make install
### Mac
git clone --recursive git://code.qt.io/qt/qt5.git -b 5.12.3 --single-branch

*  Copy the **patches** folder to qt5  
*  Apply the two patches to Qt  
cd qt5  
git apply --ignore-space-change --ignore-whitespace patches/aec.patch
cd ..

mkdir qt5-install  
mkdir qt5-build  
cd ../qt5-build

../qt5/configure -opensource -confirm-license -nomake examples -nomake tests -skip qttranslations -skip qtserialport -skip qt3d -skip qtlocation -skip qtwayland -skip qtsensors -skip qtgamepad -skip qtspeech -skip qtcharts -skip qtx11extras -skip qtmacextras -skip qtvirtualkeyboard -skip qtpurchasing -skip qtdatavis3d -no-warnings-are-errors  -no-pch -prefix ../qt5-install

make  
make install
## Problems
*configure* errors, if any, may be viewed in **config.log** and **config.summary**