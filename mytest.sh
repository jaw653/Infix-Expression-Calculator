#!/bin/bash
# Runs test.c without having to compile all that bs every time

make

gcc -Wall -Wextra -std=c99 test.c bst.o string.o integer.o

./a.out
