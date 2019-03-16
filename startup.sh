#!/usr/bin/env bash

mkdir build
cd build
conan install ..
cmake -CMAKE_BUILD_TYPE=Debug
cmake ..
make
./bin/sampleSourceCode