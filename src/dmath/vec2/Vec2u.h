#pragma once
#include "Vec2.h"

namespace DM
{
  class Vec2u : public Vec2<unsigned int>
  {
  public:
    virtual DirectX::XMVECTOR Load() const override
    {
      DirectX::XMUINT2 v(x, y);
      return DirectX::XMLoadUInt2(&v);
    }
    virtual void Store(const DirectX::XMVECTOR& xm) override
    {
      DirectX::XMUINT2 v;
      DirectX::XMStoreUInt2(&v, xm);
      x = v.x;
      y = v.y;
    }
    virtual std::string ToString() const override
    {
      return "";
    }
  };
} // namespace DM
