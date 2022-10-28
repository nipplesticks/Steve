#pragma once

#include "Resource.h"

namespace Render
{
  class ConstantBuffer : public Resource
  {
  public:
    void Create(const std::string& name, uint32 size);
  };
}