#!/usr/bin/env bash
set -e
cmake .
cd tests
:
make

make
make test