## Simple emulator of spinning slot machine reels using SFML library.
![](https://github.com/1Druid1/TestOG/blob/3a0ae0a1ee70b74e3558207357893bef99b52ee7/work.gif)

## Build on Windows with Visual Studio 2022
1. Copy repository link to clipboard
2. Visual studio-> clone repository -> paste link
3. Build and run project in Debug x86 mode <br><br>
   The executable file will be in Debug folder (to run, you need to place it in the root folder of the project next to .dll files of sfml library, and fonts folder should also be present)

### Build with cmake
1. Download zip and unzip
2. cd path/to/TestOG-master
3. cmake -S . -B build
4. cmake --build build --config Debug <br>
or cmake --build build --config Release <br><br>
The executable file will be in TestOG-master/build/Debug (or Release) folder
