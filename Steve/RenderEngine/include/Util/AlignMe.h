#pragma once

#define AlignAs(a, n)                                                                              \
  {                                                                                                \
    ((n) + ((a)-1) & ~((a)-1))                                                                     \
  }
#define AlignAs256(n) AlignAs(256u, n)
#define AlignAs128(n) AlignAs(128u, n)
#define AlignAs64(n) AlignAs(64u, n)
#define AlignAs32(n) AlignAs(32u, n)