#pragma once
#include "vec2/Vec2.h"
#include "vec3/Vec3.h"
#include "vec4/Vec4.h"
#include "mat4x4/Mat4x4.h"
#include "mat3x3/Mat3x3.h"

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

  using Mat4x4f = Mat4x4<float>;
  using Mat3x3f = Mat3x3<float>;
}