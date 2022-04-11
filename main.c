#include "pbcd.h"
#include "helper.c"

/// return codes
/// 0 success
/// 1,2 failure (malloc)
/// assume: input string encoded as simple ascii (not extended)
/// assume: printf succeeds (otherwise aborts)
int main()
{
  int status = 0;
  struct HelperData hd;
  //const char* input = "DEAD!!BEEF__"; // INPUT

  const char* input = "abc"; // INPUT
  prepareData(&hd, input);
  if (status == 1)
    goto lbl_src;
  if (status == 2)
    goto lbl_dst;
  pbcd(hd.src, hd.dst);

  // print input
  status = printf("src: %p\n", hd.src); // -pedantic suggests %s, but we want address!
  if (status < 0) abort(); // alternative: status = 2; goto lbl_src;
  for(uint32_t i=0; i<hd.src_mem_len; i+=1)
  {
    status = printf("%2u, ", hd.src[i]);
    if (status < 0) abort();
  }
  status = printf("\n");
  if (status < 0)  abort();
  // print output
  for(uint32_t i=0; i<hd.prefix_len; i+=1)
  {
    status = printf("%2u, ", hd.dst[i]);
    if (status < 0) abort();
  }
  status = printf("\n");
  if (status < 0) abort();
  for(uint32_t i=hd.prefix_len; i<hd.dst_mem_len; i+=1)
    printBits(sizeof(hd.dst[0]), &hd.dst[i]);
  status = printf("\n");
  if (status < 0) abort();
  status = 0;

lbl_dst:
  free(hd.dst); // malloced (CeilDiv(str_len,2))*sizeof(char)
lbl_src:
  free(hd.src); // malloced (prefix_len+str_len)*sizeof(char)
  return status;
}
