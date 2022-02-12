#pragma once
#include "Vec2.h"

namespace DM
{
  class Vec2i : public Vec2<int>
  {
  public:
    virtual DirectX::XMVECTOR Load() const override
    {
      DirectX::XMINT2 v(x, y);
      return DirectX::XMLoadSInt2(&v);
    }
    virtual void Store(const DirectX::XMVECTOR& xm) override
    {
      DirectX::XMINT2 v;
      DirectX::XMStoreSInt2(&v, xm);
      x = v.x;
      y = v.y;
    }
    virtual std::string ToString() const override
    {
      return "";
    }
  };
} // namespace DM
