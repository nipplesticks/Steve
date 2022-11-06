#pragma once
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Mat4x4.h"
#include "Mat3x3.h"
#include "Typedef.h"

namespace DM
{
  using Vec2i = Vec2<int32>;
  using Vec2f = Vec2<float>;
  using Vec2u = Vec2<uint32>;

  using Vec3i = Vec3<int32>;
  using Vec3f = Vec3<float>;
  using Vec3u = Vec3<uint32>;

  using Vec4i = Vec4<int32>;
  using Vec4f = Vec4<float>;
  using Vec4u = Vec4<uint32>;

  using Color2 = Vec2<uint8>;
  using Color3 = Vec3<uint8>;
  using Color4 = Vec4<uint8>;

  using Mat4x4f          = Mat4x4<float>;
  using Mat3x3f          = Mat3x3<float>;
  constexpr float PI     = DirectX::XM_PI;
  constexpr float PI2    = DirectX::XM_2PI;
  constexpr float PIDIV2 = DirectX::XM_PIDIV2;

  namespace Color
  {
    static inline Vec4f ToNormal(uint8 r, uint8 g, uint8 b, uint8 a = 255)
    {
      Vec4f c(r, g, b, a);
      c = c / 255.f;
      return c;
    }
    static inline Vec4f ToNormal(const Color4& color)
    {
      Vec4f c(color);
      c = c / 255.f;
      return c;
    }
    static inline Vec4f ToNormal(const Color3& color)
    {
      Vec4f c(color);
      c.a = 255;
      c   = c / 255.f;
      return c;
    }
    static inline Color4 ToRGBColor(float nr, float ng, float nb, float na = 1.0f)
    {
      Vec4f  color(nr, ng, nb, na);
      Color4 c = color * 255;
      return c;
    }
    static inline Color4 ToRGBColor(const Vec4f& color)
    {
      Color4 c = color * 255;
      return c;
    }
    static inline Color4 ToRGBColor(const Vec3f& color)
    {
      Color4 c = color * 255;
      c.a          = 255;
      return c;
    }
  }

  static inline float ToRad(const float& d)
  {
    return (d * PI) / 180.f;
  }
  static inline Vec2f ToRad(const Vec2f& vd)
  {
    DM::Vec2f vr;
    for (int i = 0; i < 2; i++)
      vr[i] = ToRad(vd[i]);
    return vr;
  }
  static inline Vec3f ToRad(const Vec3f& vd)
  {
    DM::Vec3f vr;
    for (int i = 0; i < 3; i++)
      vr[i] = ToRad(vd[i]);
    return vr;
  }
  static inline Vec4f ToRad(const Vec4f& vd)
  {
    DM::Vec4f vr;
    for (int i = 0; i < 4; i++)
      vr[i] = ToRad(vd[i]);
    return vr;
  }

  static inline float ToDeg(const float& r)
  {
    return (r * 180.0f) / PI;
  }
  static inline Vec2f ToDeg(const Vec2f& vr)
  {
    DM::Vec2f vd;
    for (int i = 0; i < 2; i++)
      vd[i] = ToDeg(vr[i]);
    return vr;
  }
  static inline Vec3f ToDeg(const Vec3f& vr)
  {
    DM::Vec3f vd;
    for (int i = 0; i < 3; i++)
      vd[i] = ToDeg(vr[i]);
    return vr;
  }
  static inline Vec4f ToDeg(const Vec4f& vr)
  {
    DM::Vec4f vd;
    for (int i = 0; i < 4; i++)
      vd[i] = ToDeg(vr[i]);
    return vr;
  }
} // namespace DM