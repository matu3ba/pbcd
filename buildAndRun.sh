#!/usr/bin/env sh

#future improvements: trap on overflow, tests etc
gcc -g -std=c17 main.c pbcd.c -o task2 && valgrind -s ./task2 && echo "status $?"

##  Unfortunately, -Weverything is unusable for simple pointer casts:
##  clang -g -std=c17 -Weverything main.c pbcd.c -o task2
#main.c:56:26: warning: cast from 'char *' to 'uint32_t *' (aka 'unsigned int *') increases require
#d alignment from 1 to 4 [-Wcast-align]
#  uint32_t* ptr_prefix = (uint32_t*)(src);
#                         ^~~~~~~~~~~~~~~~
#main.c:60:32: warning: format specifies type 'void *' but the argument has type 'char *' [-Wformat
#-pedantic]
#  status = printf("src: %p\n", src); // -pedantic suggests %s, but we want address!
#                        ~~     ^~~
#                        %s
#main.c:79:16: warning: cast from 'char *' to 'uint32_t *' (aka 'unsigned int *') increases require
#d alignment from 1 to 4 [-Wcast-align]
#  ptr_prefix = (uint32_t*)(dst);
#               ^~~~~~~~~~~~~~~~
#3 warnings generated.
#pbcd.c:36:32: warning: cast from 'char *' to 'uint32_t *' (aka 'unsigned int *') increases require
#d alignment from 1 to 4 [-Wcast-align]
#    const uint32_t src_len = *((uint32_t*)(src));
#                               ^~~~~~~~~~~~~~~~
#1 warning generated.

