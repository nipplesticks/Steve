#pragma once
#include "Resource.h"

class Texture2D : public Resource
{
public:
  Texture2D()  = default;
  ~Texture2D() = default;
  void Create(uint width, uint height, DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM)
  {
    Init(Resource_Type::Texture2D, width, format, height);
  }
};