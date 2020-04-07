A simple JVM written in C++ (Still under development)

[![Build Status](https://travis-ci.com/soleverlee/avm.svg?branch=master)](https://travis-ci.com/soleverlee/avm)

# Build source

This project is created using CMake, so generally you can compile it in Linux/Windows/Mac.

## Build with Cmake

Using cmake to generate platform-specific make file or project:

```bash
git clone https://github.com/soleverlee/avm.git
cd avm
mkdir build
cd build
cmake ../
```

Then build using `make` for linux, and open `avm.sln` in Visual Studio for windows.

## Other options
There is `another_vm.sln` for Visual Studio, you may get better experience then the cmake generated one.

For users using Eclipse-CDT, you're able to import the project directly by `New C/C++Project->Empty  or Existing CMake Project".
