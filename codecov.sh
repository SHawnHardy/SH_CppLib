#!/usr/bin/env bash

# ===== Copyright =====
# @source https://github.com/codecov/example-cpp11-cmake/blob/master/.travis.yml
# @original author
#  - RokKos - RokKos
#  - Rolf Eike Beer - DerDakon
# @copyright MIT License
# have modified by SHawnHardy

cd build

# capture coverage info
lcov --directory . --capture --output-file coverage.info
# filter out system
lcov --remove coverage.info '/usr/*' '/usr/lib/*' --output-file coverage.info
# debug info
lcov --list coverage.info
# Uploading report to CodeCov
bash <(curl -s https://codecov.io/bash) || echo "Codecov did not collect coverage reports"
