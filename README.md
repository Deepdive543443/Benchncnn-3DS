## self-brewing
This repository will benchmark NCNN model on your 3DS (or OOM).
![IMG_20231010_094340](https://github.com/Deepdive543443/self-brewing/assets/83911295/7b7c3796-1888-4ad3-bb99-67163af787d1)

## Download
3dsx(Require Homebrew Launcher): https://drive.google.com/file/d/1tncRGAw0qgvCUywyteHZJxzInodQ6yAi/view?usp=drive_link


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
