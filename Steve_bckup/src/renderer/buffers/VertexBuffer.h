#pragma once

#include "Resource.h"

class VertexBuffer : public Resource
{
public:
  VertexBuffer() = default;
  ~VertexBuffer() = default;
  void Create(uint sizeOfVertex, uint numberOfVertices)
  {
    Init(Resource_Type::VertexBuffer,
         sizeOfVertex * numberOfVertices,
         DXGI_FORMAT_UNKNOWN,
         1,
         1,
         numberOfVertices);
  }
};