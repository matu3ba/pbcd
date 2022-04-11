#include "pbcd.h"

struct HelperData {
  uint32_t prefix_len;
  uint32_t str_len;
  uint32_t src_mem_len;
  char* src;
  uint32_t* ptr_prefix;
  uint32_t dst_pbcd_len;
  uint32_t dst_mem_len;
  char* dst;
};

/// assume: continuous data pointed by to by str is terminated with 0x00
/// assume: len(str) <= UINT32_MAX
uint32_t Str_Len(const char* str);

/// assume: continuous data pointed by input of size >= strlen
/// assume: str2 has sufficient backed memory size
/// copy strlen chars from str to str2
void Str_Copy(const char* str, uint32_t strlen, char* str2);

/// assume: positive number
/// assume: x + y does not overflow
/// computes x/y
uint32_t CeilDiv_AssumeU32(uint32_t x, uint32_t y);

/// on success allocates data for hd.src and hd.dst
/// on allocation failure for hd.src returns 1
/// on allocation failure for hd.dst returns 2
int prepareData(struct HelperData* hd, const char* input);

uint32_t Str_Len(const char* str)
{
    const char* tmps = str;
    while(*tmps != 0)
      tmps++;
    return (uint32_t)(tmps-str);
}

void Str_Copy(const char* str, uint32_t strlen, char* str2)
{
    for(uint32_t i=0; i<strlen; i+=1)
        str2[i] = str[i];
}

uint32_t CeilDiv_AssumeU32(uint32_t x, uint32_t y)
{
    return (x + y - 1) / y; // y=2 => x+1/2
}

int prepareData(struct HelperData* hd, const char* input)
{
  hd->prefix_len = 4;
  hd->str_len = Str_Len(input);
  hd->src_mem_len = hd->prefix_len+hd->str_len;
  hd->src = malloc((hd->src_mem_len)*sizeof(char));
  if (hd->src == NULL)
    return 1;
  hd->ptr_prefix = (uint32_t*)(hd->src);
  *hd->ptr_prefix = hd->str_len;
  Str_Copy(input, hd->str_len, &hd->src[hd->prefix_len]);

  hd->dst_pbcd_len = CeilDiv_AssumeU32(hd->str_len, 2);
  hd->dst_mem_len = hd->prefix_len+hd->dst_pbcd_len;
  hd->dst = calloc(hd->dst_mem_len, sizeof(char));
  if(hd->dst == NULL)
    return 2;
  hd->ptr_prefix = (uint32_t*)(hd->dst);
  *hd->ptr_prefix = hd->dst_pbcd_len;
  return 0;
}
