## Benchncnn-3DS  
This repository will benchmark NCNN model on your 3DS (or OOM).
![IMG_20231010_173034](https://github.com/Deepdive543443/Benchncnn-3DS/assets/83911295/9eee9fe3-8ef4-4c42-99cf-2e9c5eedca21)


## Download
3dsx(Require Homebrew Launcher): https://drive.google.com/file/d/1tncRGAw0qgvCUywyteHZJxzInodQ6yAi/view?usp=drive_link

## Performance and issues
At this moment, to make the application runs at first, we built the NCNN with OpenMP and SimpleOMP off, so it will takes (lots of) times to run an entire benchmarking (nearly 2min for nanodet_m to finish a benchmark on 320x320 image). We will try look into the best setting with improved performance on 3DS.

Larger networks will cause the program to crash, some of them are larger than the FCRAM of 3DS (128mb).


## Build
To build this program, you will need to:
- Install devkitARM
  - If you are working on windows, download DevkitPro installer from [DevkitPro](https://devkitpro.org/wiki/Getting_Started).
  - If you are on using Ubuntu like me, the guidelines from DevkitPro might not work for you. Try using the lines below to install 
  ```
  sudo apt-get update
  sudo apt-get upgrade
  wget https://apt.devkitpro.org/install-devkitpro-pacman
  chmod +x ./install-devkitpro-pacman
  sudo ./install-devkitpro-pacman
  ```
  
  ```
  export DEVKITPRO=/opt/devkitpro
  export DEVKITARM=${DEVKITPRO}/devkitARM
  export DEVKITPPC=${DEVKITPRO}/devkitPPC
  export export PATH=${DEVKITPRO}/tools/bin:$PATH
  source ~/.profile
  ```
  ```
  sudo dkp-pacman -Sy
  sudo dkp-pacman -Syu
  sudo dkp-pacman -S 3ds-dev
  ```
- [Download](https://drive.google.com/file/d/1MpEv8hHO_Z7lfZT23nGj9IqDHolVRaIT/view?usp=drive_link) or build NCNN using toolchains file from [3DS-cmake](https://github.com/Xtansia/3ds-cmake).
  

  Copy the toolchain files (DevitARM3DS.cmake and the cmake folder) from [3DS-cmake](https://github.com/Xtansia/3ds-cmake), then build NCNN using:
  ```
  cd ncnn
  mkdir build && cd build
  cmake -DCMAKE_TOOLCHAIN_FILE=../toolchains/DevkitArm3DS.cmake .. -DNCNN_SIMPLEOCV=ON -DNCNN_OPENMP=OFF -DNCNN_BENCHMARK=ON ..
  make -j4
  make install
  ```
- Modify the NCNN_DIR in Makefile to your NCNN path, it should good to go
- (Optional) Install Citra 3DS emulator for debugging 
- (Optional) Use FTPD Pro to transfer files between 3DS and PC

## Credit
- [NCNN](https://github.com/Tencent/ncnn): High performance neural network inference computing framework for mobile platform, easy to use and port
- [DevkitPRO](https://devkitpro.org/wiki/Getting_Started): Toolchain for 3DS homebrew development
- [3DS-cmake](https://github.com/Xtansia/3ds-cmake): Toolchain files to build CMake project for 3DS
- [FTPD-Pro](https://github.com/mtheall/ftpd): FTP Server for 3DS/Switch/Linux.
- [Citra](https://github.com/citra-emu/citra): 3DS emulator for Windows, Linux, and MacOS
