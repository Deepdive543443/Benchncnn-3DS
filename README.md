## Benchncnn-3DS  
![IMG_20231010_173034](https://github.com/Deepdive543443/Benchncnn-3DS/assets/83911295/9eee9fe3-8ef4-4c42-99cf-2e9c5eedca21)

## Intro
This repository is a port of Benchncnn of Nintendo 3DS, which is used to testing the performance of neural network in NCNN's format.
Because of limited amount of memory(64mb), this project could only be used for testing light-weight networks.


## Download
This toolkit required a modded Nintendo 3DS with an title manager or Homebrew Launcher to boot.

3DSX, CIA and pre-build NCNN lib available at: https://github.com/Deepdive543443/Benchncnn-3DS/releases

Copy the .param file to the "models" folder to the root of your SD card 

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
  export DEVKITARM=/opt/devkitpro/devkitARM
  export DEVKITPPC=/opt/devkitpro/devkitPPC
  export export PATH=$/opt/devkitpro/tools/bin:$PATH
  source ~/.profile
  ```
  ```
  sudo dkp-pacman -Sy
  sudo dkp-pacman -Syu
  sudo dkp-pacman -S 3ds-dev
  ```
- [Download](https://drive.google.com/file/d/1MpEv8hHO_Z7lfZT23nGj9IqDHolVRaIT/view?usp=drive_link) or build NCNN library.
  

  Copy the toolchain files (DevitARM3DS.cmake) to the toolchains folder of NCNN.

  Then build NCNN using:
  ```
  cd ncnn
  mkdir build && cd build
  cmake -DCMAKE_TOOLCHAIN_FILE=../toolchains/DevkitArm3DS-toolchain.cmake -DNCNN_SIMPLEOCV=ON -DNCNN_OPENMP=OFF -DNCNN_SIMPLEVK=OFF -DNCNN_VFPV4=OFF ..
  make -j4
  make install
  ```
- Modify the NCNN_DIR in Makefile to your NCNN path, it should good to go
- (Optional) Install Citra 3DS emulator for debugging 
- (Optional) Use FTPD Pro to transfer files between 3DS and PC


## Performance and issues
At this moment, to make the application runs at first, we built the NCNN with OpenMP and SimpleOMP off, so it will takes (lots of) times to run an entire benchmarking (nearly 2min for nanodet_m to finish a benchmark on 320x320 image). We will try look into the best setting with improved performance on 3DS.

Larger networks will cause the program to crash, some of them are larger than the FCRAM of 3DS (128mb).

Old 3DS's cpu only have one core available to use. Multithreat might be available on newer 3DS model

## Todo
- Extended memory modes

## Credit
- [NCNN](https://github.com/Tencent/ncnn): High performance neural network inference computing framework for mobile platform, easy to use and port
- [DevkitPRO](https://devkitpro.org/wiki/Getting_Started): Toolchain for 3DS homebrew development
- [3DS-cmake](https://github.com/Xtansia/3ds-cmake): Toolchain files to build CMake project for 3DS
- [FTPD-Pro](https://github.com/mtheall/ftpd): FTP Server for 3DS/Switch/Linux.
- [Citra](https://github.com/citra-emu/citra): 3DS emulator for Windows, Linux, and MacOS
