#!/usr/bin/env bash
cmake .
make
ctest
if [ $? -ne 0 ]; then
  ./bin/unit_tests
fi
