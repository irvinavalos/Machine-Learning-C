#!/bin/sh

mkdir -p build/
gcc -Wall -Wextra -Iinclude/linear_algebra -o build/tests src/linear_algebra/*.c tests/tests.c -lm
