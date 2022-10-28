#pragma once
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Mat4x4.h"
#include "Mat3x3.h"

namespace DM
{
  using Vec2i = Vec2<int>;
  using Vec2f = Vec2<float>;
  using Vec2u = Vec2<unsigned int>;

  using Vec3i = Vec3<int>;
  using Vec3f = Vec3<float>;
  using Vec3u = Vec3<unsigned int>;

  using Vec4i = Vec4<int>;
  using Vec4f = Vec4<float>;
  using Vec4u = Vec4<unsigned int>;

  using Mat4x4f          = Mat4x4<float>;
  using Mat3x3f          = Mat3x3<float>;
  constexpr float PI     = DirectX::XM_PI;
  constexpr float PI2    = DirectX::XM_2PI;
  constexpr float PIDIV2 = DirectX::XM_PIDIV2;

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