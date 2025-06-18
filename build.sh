#!/bin/sh

mkdir -p build/
gcc -Wall -Wextra -Iinclude/linear_algebra -Iinclude/data -o build/tests src/linear_algebra/*.c src/data/*.c tests/tests.c -lm
