# Pong
Classic Pong game with SDL2

## Requirements
+ SDL2 v2.0.5
+ SDL2_ttf v2.0.1


## Running on Linux
### g++ v4.x
+ Compile
```
make all
```
+ Run
```
./pong
```
### g++ v5.x
In makefile replace ```-std=c++1y``` with ```-std=c++14```. Compiling and running same as above in v4.x

## Running on Windows
### Visual Studio 2015
+ Grab SDL2 and SDL2_ttf development libraries, add them to linker and copy dlls in.exe directory.