#pragma once
#include "Typedef.h"
struct Vector2u
{
  Vector2u(uint _x = 0, uint _y = 0)
  {
    x = _x;
    y = _y;
  }
  uint x;
  uint y;
};

struct Vector2i
{
  Vector2i()
  {
    x = 0;
    y = 0;
  }
  int x;
  int y;
};