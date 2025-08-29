# Project Overview

Process json data using C programming language.

# Build Instructions

1. Install CMake (version 3.12.4 or higher).
2. Clone the repository:
   ```
   git clone --recursive https://github.com/Learning-BaoDoan/project-process-ex.git
   cd project-process-ex
   ```
3. Configure CMake:
```powershell
cd project-ex
cmake -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE=../toolchain_win.cmake -DPRE_TEST_FIRMWARE=ON -B build .
cmake -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE=../toolchain_win.cmake -DPRE_TEST_FIRMWARE=OFF -B build .
```

4. Build the project:
```powershell
mingw32-make -C build -j20
```