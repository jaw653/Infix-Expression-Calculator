#!/bin/bash
# Test the bst utility

make

gcc -Wall -Wextra -std=c99 testBST.c bst.o string.o scanner.o -o runBSTtest

./runBSTtest
