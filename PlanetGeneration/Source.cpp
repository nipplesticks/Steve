#include <iostream>
#include <common/DMath.h>
#include "generation/Generation.h"

int main()
{
  Generation::Create("", 11, {0, 3, 5, 7, 8, 9, 10, 11});

  return 0;
}