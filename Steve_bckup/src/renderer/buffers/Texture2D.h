#pragma once
#include "Resource.h"
#include "../d3d12/myRenderer.h"
class Texture2D : public Resource
{
public:
  Texture2D()  = default;
  ~Texture2D() = default;
  void Create(uint width, uint height, DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM)
  {
    Init(Resource_Type::Texture2D, width, format, height);
  }
  template<typename T>
  T GetPixel(uint x, uint y);
};

template <typename T>
inline T Texture2D::GetPixel(uint x, uint y)
{
  T d = T();
  MyRenderer::GetInstance()->GetResource(
      this, &d, (x + y * myDimention.x) * myElementSize, myElementSize);
  return d;
}
