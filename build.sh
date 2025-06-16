#!/bin/sh

mkdir -p build/
gcc -Wall -Wextra -Iinclude -o build/tests src/vector.c src/matrix.c tests/tests.c -lm
