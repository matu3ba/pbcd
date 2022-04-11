#include "pbcd.h"
#include "helper.c"
#include <tau/tau.h>

//const char* input = "DEAD!!BEEF__"; // INPUT
TAU_MAIN()

//prepare
TEST(foo, bar1)
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

lbl_dst:
  free(hd.dst); // malloced (CeilDiv(str_len,2))*sizeof(char)
lbl_src:
  free(hd.src); // malloced (prefix_len+str_len)*sizeof(char)
  CHECK_EQ(status, 0);
  CHECK_EQ(hd.dst, 0xabc0); // TODO docs: how do we compare pointer addresses?
}
