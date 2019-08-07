#!/usr/bin/env bash
set -e
cmake .
make
ctest
./bin/unit_tests