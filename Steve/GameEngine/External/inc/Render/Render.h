#pragma once

#include <Common/Transform.h>
#include <Common/Typedef.h>

class Render
{
public:
  static Render gRender;

public:
  Render();

  void Print();

private:
  Transform myTransform;
  uint64    myU64;
};