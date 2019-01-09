#!/usr/bin/env bash

echo "======== install gtest ========="
git clone https://github.com/google/googletest.git ./gtest
cd gtest
cmake ./ && make && sudo make install

echo "========== test gtest =========="
cd googletest/make
make && ./sample1_unittest
