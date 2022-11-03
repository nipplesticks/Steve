#pragma once
#include "Resource.h"


namespace Render
{
  class VertexBuffer : public Resource
  {
  public:
    void Create(const std::string& name, uint32 vertexSize, uint32 numVertices);
    virtual uint32 GetClassSize() const;
  };
} // namespace Render