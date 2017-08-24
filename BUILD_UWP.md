This is a stand-alone guide for creating your first High Fidelity build for Windows 64-bit.

## Building High Fidelity
Note: We are now using Visual Studio 2017 and Qt 5.9.1. If you are upgrading from Visual Studio 2013 and Qt 5.6.2, do a clean uninstall of those versions before going through this guide. 

Note: The prerequisites will require about 10 GB of space on your drive.

### Step 1. Visual Studio 2017

If you don’t have Community or Professional edition of Visual Studio 2017, download [Visual Studio Community 2017](https://www.visualstudio.com/downloads/). 

When selecting components, select both "Desktop development with C++" and "Universal Windows Platform development".
Also check "Windows 8.1 SDK and UCRT SDK" and "VC++ 2015.3 v140 toolset (x86,x64)" on the Summary toolbar on the right.

### Step 2. Installing CMake

Download and install the latest version of CMake 3.9. Download the file named  win64-x64 Installer from the [CMake Website](https://cmake.org/download/). Make sure to check "Add CMake to system PATH for all users" when prompted during installation.

### Step 3. Installing Qt

Download and install the [Qt Online Installer](https://www.qt.io/download-open-source/?hsCtaTracking=f977210e-de67-475f-a32b-65cec207fd03%7Cd62710cd-e1db-46aa-8d4d-2f1c1ffdacea). While installing, you only need to have the following components checked under Qt 5.9.1:

* "UWP x64 (MSVC2017)
* "msvc2017 64-bit"
* "Qt WebEngine"
* "Qt Script (Deprecated)".

Note: Installing the Sources is optional but recommended if you have room for them (~2GB). 

### Step 4. Setting Qt Environment Variable

Go to `Control Panel > System > Advanced System Settings > Environment Variables > New...` (or search “Environment Variables” in Start Search).
* Set "Variable name": `QT_CMAKE_PREFIX_PATH`
* Set "Variable value": `C:\Qt\5.9.1\msvc2017_64\lib\cmake` 

As we are using UWP, add another variable (the first is used for non-UWP builds)
* Set "Variable name": `QT_CMAKE_PREFIX_PATH_UWP`
* Set "Variable value": `C:\Qt\5.9.1\winrt_x64_msvc2017\lib\cmake` 

### Step 5. Installing OpenSSL

Download and install the Win64 OpenSSL v1.0.2 Installer[https://slproweb.com/products/Win32OpenSSL.html].

UWP needs a version of OpenSSL that has been built through vcpgk.
* Clone GitHub repository for vcpkg (<https://github.com/Microsoft/vcpkg>)
* Open console and __cd__ to the vcpkg directory
* Create vcpkg.exe: __>powershell -exec bypass scripts\bootstrap.ps1__
* Build OpenSSL: __vcpkg install openssl:x64-uwp__.  This will create a folder named x64-uwp in the ..vcpkg/installed folder.
* Create a new environment variable: Name: VCPKG_PATH,  Value: the path to the vcpkg 'installed/x64-uwp' folder.

### Step 6. zlib

(Assumes step 5 has been completed)  
In the vcpkg directory, build zlib: __vcpkg install zlib:x64-uwp__.


### Step 7. bullet

(Assumes step 5 has been completed)  
In the vcpkg directory, build bullet: __vcpkg install bullet3:x64-uwp__.

BUILDING MAY FAIL!!!  To fix this, modify lines 3036-3038 in ..vcpkg\buildtrees\bullet3\src\bullet3-2.86.1\src\BulletSoftBody by adding __= nullptr;__  instead of the semicolon on each line

            btRigidBody* rigidCol = nullptr;
            btMultiBodyLinkCollider* multibodyLinkCol = nullptr;
            btScalar* deltaV = nullptr;

### Step 8. glm

(Assumes step 5 has been completed)  
In the vcpkg directory, build zlib: __vcpkg install glm:x64-uwp__.

### Step 9. Scribe

High Fidelity has a shader pre-processing tool called `scribe` that various libraries will call on during the build process. You must compile scribe using your native toolchain (following the build instructions for your platform) and then pass a CMake variable or set an ENV variable `SCRIBE_PATH` that is a path to the scribe executable.

CMake will fatally error if it does not find the scribe executable while using the android tool-chain.
### Step 10. Running CMake to Generate Build Files

Run Command Prompt from Start and run the following commands:
```
cd "%HIFI_DIR%"
mkdir build
cd build
cmake .. -G "Visual Studio 15 Win64" -DUWP=TRUE
```
    
Where `%HIFI_DIR%` is the directory for the highfidelity repository.     

### Step 11. Making a Build
Verify that High-Fidelity is not running.

Open `%HIFI_DIR%\build\hifi.sln` using Visual Studio.

Change the Solution Configuration (next to the green play button) from "Debug" to "Release" for best performance.

Run `Build > Build Solution`.

Note that Visual Studio may need to install additional components for UWP.  This will require closing Visual Studio.
### Step 12. Testing Interface

Create another environment variable (see Step #4)
* Set "Variable name": `_NO_DEBUG_HEAP`
* Set "Variable value": `1`

In Visual Studio, right+click "interface" under the Apps folder in Solution Explorer and select "Set as Startup Project". Run `Debug > Start Debugging`.

Now, you should have a full build of High Fidelity and be able to run the Interface using Visual Studio. Please check our [Docs](https://wiki.highfidelity.com/wiki/Main_Page) for more information regarding the programming workflow.

Note: You can also run Interface by launching it from command line or File Explorer from `%HIFI_DIR%\build\interface\Release\interface.exe`

## Troubleshooting

For any problems after Step #6, first try this: 
* Delete your locally cloned copy of the highfidelity repository
* Restart your computer
* Redownload the [repository](https://github.com/highfidelity/hifi) 
* Restart directions from Step #6

#### CMake gives you the same error message repeatedly after the build fails

Remove `CMakeCache.txt` found in the `%HIFI_DIR%\build` directory.

#### Qt is throwing an error

Make sure you have the correct version (5.9.1) installed and `QT_CMAKE_PREFIX_PATH` environment variable is set correctly.
