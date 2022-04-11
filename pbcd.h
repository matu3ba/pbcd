#ifndef PBCD_H
#define PBCD_H

#include "common.h"

/// assume: src points to string with 4 byte len_info prefixed
/// assume: dst points to string with 4 byte len_info prefixed, len == ceil(len_src/2)
/// Function to convert string into packed-binary-digit format
/// by zeroing out characters non-representable as hex and concatenating the result
/// per 4 bit/nibble (hex) padded by zeroes, if necessary.
/// Example:
/// src points to (2*U8) with “4F”
/// [2, 0, 0, 0, 0x34 (number 4), 0x46 (char F)]
/// binary representations 0x34 (00110100b), 0x46 (01000110b)
/// dst points to (1*U8) 01001111b
void pbcd(char* src, char* dst);

void printBits(int32_t const size, void * const ptr);

#endif // PBCD_H
