# fpscli

A rough approximation of a First Person Shooter, done on the command line.

Please see the source file on how to configure your command line before running.

Windows and Linux versions are available. See the relevant source directory for details.

### Credit where credit is due

Big thank you to [OneLoneCoder](https://github.com/OneLoneCoder) for building the groundwork for this

Big thanks as well to [rohanliston](https://github.com/rohanliston) for porting this to Linux and providing build files

We're gonna make... something cool with this. I don't know what that thing will be.

![image](https://user-images.githubusercontent.com/42927786/105610007-f0aa0680-5d7a-11eb-837e-1d5f61f94bd0.png)

## Prerequisites

* CMake - C/C++ build system
* NCursesw - Library for interacting with the terminal

### Installation

* Ubuntu: `sudo apt-get install cmake libncursesw5-dev`
* Fedora: `sudo dnf -y install cmake ncurses-devel`
* Other distros: `¯\_(ツ)_/¯`

## Build

```sh
mkdir build
cd build
cmake ..
make
```

## Run

`./CommandLineFPS`


