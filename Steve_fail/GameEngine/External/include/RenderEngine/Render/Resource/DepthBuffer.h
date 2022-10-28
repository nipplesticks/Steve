#pragma once

#include "Resource.h"

namespace Render
{
  class DepthBuffer : public Resource
  {
  public:
    void Create(const std::string& name, uint16 width, uint16 height);
  };
}