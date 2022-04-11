#include "pbcd.h"

// assume: little endian
//void printBits(int32_t const size, void const * const ptr)
void printBits(int32_t const size, void * const ptr)
{
    int status = 0;
    unsigned char *b = (unsigned char*) ptr; // generic pointer (void)
    //unsigned char byte;
    for (int32_t i = size-1; i >= 0; i-=1)
    {
        //for (int32_t j = 7; j >= 0; j-=1)
        //{
        //    // shift out right part and take rightmost bit
        //    unsigned char byte = (b[i] >> j) & 1;
        //    status = printf("%u", byte);
        //    if (status < 0) abort();
        //}
        status = printf("%x", b[i]);
        if (status < 0) abort();
    }
    //printf(" ");
    status = puts(""); // write empty string followed by newline
    if (status < 0) abort();
}

void pbcd(char* src, char* dst)
{
    // src: [len (4B), U8, U8, ..]
    const uint32_t start_data = 4;
    const uint32_t src_len = *((uint32_t*)(src));
    const char* src_data = &src[start_data];
    char* dst_data = &dst[start_data];
    uint32_t dst_i;
    bool even = false;
    for (uint32_t i = 0; i<src_len; i+=1)
    {
        assert(i<src_len);
        dst_i = i/2; // 0:01, 1:23, 2:45, 3:67, 4:8..
        char hex;
        if (48 <= src_data[i] && src_data[i] <= 57)
            hex = src_data[i] - 48; // 0..9
        else if (65 <= src_data[i] && src_data[i] <= 70)
            hex = src_data[i] - 55; // 10..15
        else if (97 <= src_data[i] && src_data[i] <= 102)
            hex = src_data[i] - 87; // 10..15
        else
            hex = 0;
        if(even == true)
        {
            dst_data[dst_i] |= hex;
            even = false;
        }
        else
        {
            dst_data[dst_i] |= (hex << 4);
            even = true;
        }
    }
}
