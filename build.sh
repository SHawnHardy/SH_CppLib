#!/usr/bin/env bash

echo "============ build ============="
rm -rf ./build
mkdir build
cd build
cmake ../ && make && make CTEST_OUTPUT_ON_FAILURE=1 test