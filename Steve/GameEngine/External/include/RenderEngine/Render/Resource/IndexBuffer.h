#pragma once

#include "Resource.h"

namespace Render
{
  class IndexBuffer : public Resource
  {
  public:
    void Create(const std::string& name, uint32 numIndices);
  };
} // namespace Render