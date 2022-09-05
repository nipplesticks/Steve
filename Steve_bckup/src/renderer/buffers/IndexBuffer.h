#pragma once

#include "Resource.h"

class IndexBuffer : public Resource
{
public:
  IndexBuffer()   = default;
  ~IndexBuffer() = default;
  void Create(uint numberOfIndices)
  {
    Init(Resource_Type::IndexBuffer,
         numberOfIndices * sizeof(uint),
         DXGI_FORMAT_UNKNOWN,
         1,
         1,
         numberOfIndices);
  }
};