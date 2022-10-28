#pragma once

#define AlignAs(a, n)                                                                              \
  {                                                                                                \
    ((n) + ((a)-1) & ~((a)-1))                                                                     \
  }
#define AlignAs256(n) AlignAs(256, (n))
#define AlignAs128(n) AlignAs(128, (n))
#define AlignAs64(n) AlignAs(64, (n))
#define AlignAs32(n) AlignAs(32, (n))