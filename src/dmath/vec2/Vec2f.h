#pragma once
#include "Vec2.h"

namespace DM
{
  class Vec2f : public Vec2<float>
  {
  public:
    virtual DirectX::XMVECTOR Load() const override
    {
      DirectX::XMFLOAT2 v(x, y);
      return DirectX::XMLoadFloat2(&v);
    }
    virtual void Store(const DirectX::XMVECTOR& xm) override
    {
      DirectX::XMFLOAT2 v;
      DirectX::XMStoreFloat2(&v, xm);
      x = v.x;
      y = v.y;
    }
    virtual std::string ToString() const override
    {
      return "";
    }
  };
} // namespace DM
