#include <stdio.h> // printf/puts for simplicity
#include <stdlib.h> // malloc for usability + simplicity
#include "pbcd.h"

uint32_t Str_Len(const char* str);
void Str_Copy(const char* str, uint32_t strlen, char* str2);
uint32_t CeilDiv_AssumeU32(uint32_t x, uint32_t y);

/// assume: continuous data pointed by to by str is terminated with 0x00
/// assume: len(str) <= UINT32_MAX
uint32_t Str_Len(const char* str)
{
    const char* tmps = str;
    while(*tmps != 0)
      tmps++;
    return (uint32_t)(tmps-str);
}

/// assume: continuous data pointed by input of size >= strlen
/// assume: str2 has sufficient backed memory size
/// copy strlen chars from str to str2
void Str_Copy(const char* str, uint32_t strlen, char* str2)
{
    for(uint32_t i=0; i<strlen; i+=1)
        str2[i] = str[i];
}

/// assume: positive number
/// assume: x + y does not overflow
/// computes x/y
uint32_t CeilDiv_AssumeU32(uint32_t x, uint32_t y)
{
    return (x + y - 1) / y; // y=2 => x+1/2
}

/// return codes
/// 0 success
/// 1 failure (mallo)
/// assume: input string encoded as simple ascii (not extended)
/// assume: printf succeeds (otherwise aborts)
int main()
{
  int status = 0;
  const uint32_t prefix_len = 4;
  //const char* input = "DEAD!!BEEF__"; // INPUT
  const char* input = "abc"; // INPUT

  const uint32_t str_len = Str_Len(input);
  uint32_t src_mem_len = prefix_len+str_len;

  char* src = malloc((src_mem_len)*sizeof(char));
  if (src == NULL)
    return 1;
  uint32_t* ptr_prefix = (uint32_t*)(src);
  *ptr_prefix = str_len;
  Str_Copy(input, str_len, &src[prefix_len]);

  status = printf("src: %p\n", src); // -pedantic suggests %s, but we want address!
  if (status < 0) abort(); // alternative: status = 2; goto lbl_src;
  for(uint32_t i=0; i<src_mem_len; i+=1)
  {
    status = printf("%2u, ", src[i]);
    if (status < 0) abort();
  }
  status = printf("\n");
  if (status < 0)  abort();

  uint32_t dst_pbcd_len = CeilDiv_AssumeU32(str_len, 2);
  uint32_t dst_mem_len = prefix_len+dst_pbcd_len;

  char* dst = calloc(dst_mem_len, sizeof(char));
  if(dst == NULL)
  {
      status = 1;
      goto lbl_src;
  }
  ptr_prefix = (uint32_t*)(dst);
  *ptr_prefix = dst_pbcd_len;

  pbcd(src, dst);

  // print result
  for(uint32_t i=0; i<prefix_len; i+=1)
  {
    status = printf("%2u, ", dst[i]);
    if (status < 0) abort();
  }
  status = printf("\n");
  if (status < 0) abort();
  for(uint32_t i=prefix_len; i<dst_mem_len; i+=1)
    printBits(sizeof(dst[0]), &dst[i]);
  status = printf("\n");
  if (status < 0) abort();
  status = 0;

//lbl_dst:
  free(dst); // malloced (CeilDiv(str_len,2))*sizeof(char)
lbl_src:
  free(src); // malloced (prefix_len+str_len)*sizeof(char)
  return status;
}
