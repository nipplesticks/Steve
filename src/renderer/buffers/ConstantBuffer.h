#pragma once

#include "Resource.h"

class ConstantBuffer : public Resource
{
public:
  ConstantBuffer()  = default;
  ~ConstantBuffer() = default;
  void Create(uint size)
  {
    Init(Resource_Type::ConstantBuffer, size);
  }
};