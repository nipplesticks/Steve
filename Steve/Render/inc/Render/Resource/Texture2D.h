#pragma once
#include "Resource.h"

namespace Render
{
  class Texture2D : public Resource
  {
  public:
    void Create(const std::string& name,
                uint32             width,
                uint32             height,
                DXGI_FORMAT        format    = DXGI_FORMAT_R8G8B8A8_UNORM,
                bool               cpuAccess = false);
    virtual uint32 GetClassSize() const;
  };
} // namespace Render