#!/bin/sh

mkdir -p build/
gcc -Wall -Wextra -Iinclude -o build/vector src/vector.c tests/test_vector.c -lm
