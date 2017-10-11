#!/bin/bash
# Test the bst utility

make

gcc -Wall -Wextra -std=c99 bst.c string.o scanner.o -o runBSTtest

./runBSTtest
