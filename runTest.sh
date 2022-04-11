#!/usr/bin/env sh

#gcc -g -std=c17 test.c pbcd.c -o task2 && valgrind -s ./task2 && echo "status $?"
clang -I tau -g -std=c17 -Weverything test.c pbcd.c -o task2
