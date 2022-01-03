[![CMake](https://github.com/daniel-meilak/Advent-of-Code-2020/actions/workflows/cmake.yml/badge.svg)](https://github.com/daniel-meilak/Advent-of-Code-2020/actions/workflows/cmake.yml)

## Advent of Code 2020

Coding up each day of AoC 2020 using C++. Nothing too new however I have just started using Visual Studio Code as it has good integration with WSL2 which I have been using for work for the last few years. Debugging integration using GDB is also possible and hence I have been been learning to use GDB in a GUI environment. 

Started:  04 Dec 2020  
Finished: 25 Dec 2020

Some new things I've learned:
- better understanding of GDB
- different containers: vector, list, deque
    - though still need to understand pros/cons better!
- usage of maps and unordered maps
- examples of function templates

### Testing:
CMake is configured for testing each day against my input solutions. To use, create a build directory and run `cmake [source_directory]`, followed by `make` to compile the source code. `CTest` can be used to run the test suite.