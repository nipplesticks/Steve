#pragma once
#include "Resource.h"

namespace Render
{
  class StructuredBuffer : public Resource
  {
  public:
    void Create(const std::string& name, uint32 elementSize, uint32 numElements);
    virtual uint32 GetClassSize() const;
  };
} // namespace Render