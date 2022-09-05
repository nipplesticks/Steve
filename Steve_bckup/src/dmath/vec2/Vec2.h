#pragma once
#include <DirectXMath.h>
#include <cstddef>
#include <string>
#include <sstream>

#pragma region ForwardDeclarations
template <class U>
class Vec3;
template <class U>
class Vec4;
template <class U>
class Mat3x3;
template <class U>
class Mat4x4;
#pragma endregion
template <class T>
class Vec2
{
public:
#pragma region Constructors
  Vec2();
  template <class U>
  Vec2(U v);
  template <class U, class V>
  Vec2(U _x, V _y);
  template <class U>
  Vec2(const Vec2<U>& vec2);
  template <class U>
  Vec2(const Vec3<U>& vec3);
  template <class U>
  Vec2(const Vec4<U>& vec4);
  Vec2(const DirectX::XMINT2& xm);
  Vec2(const DirectX::XMINT3& xm);
  Vec2(const DirectX::XMINT4& xm);

  Vec2(const DirectX::XMUINT2& xm);
  Vec2(const DirectX::XMUINT3& xm);
  Vec2(const DirectX::XMUINT4& xm);

  Vec2(const DirectX::XMFLOAT2& xm);
  Vec2(const DirectX::XMFLOAT3& xm);
  Vec2(const DirectX::XMFLOAT4& xm);
  Vec2(const DirectX::XMFLOAT2A& xm);
  Vec2(const DirectX::XMFLOAT3A& xm);
  Vec2(const DirectX::XMFLOAT4A& xm);
  Vec2(const DirectX::XMVECTOR& xm);
#pragma endregion
#pragma region VectorOperatiors
  // Asignment Operators
  template <class U>
  Vec2<T>& operator=(const U& v);
  template <class U>
  Vec2<T>& operator=(const Vec2<U>& vec2);
  template <class U>
  Vec2<T>& operator=(const Vec3<U>& vec3);
  template <class U>
  Vec2<T>& operator=(const Vec4<U>& vec4);
  Vec2<T>& operator=(const DirectX::XMINT2& xm);
  Vec2<T>& operator=(const DirectX::XMINT3& xm);
  Vec2<T>& operator=(const DirectX::XMINT4& xm);
  Vec2<T>& operator=(const DirectX::XMUINT2& xm);
  Vec2<T>& operator=(const DirectX::XMUINT3& xm);
  Vec2<T>& operator=(const DirectX::XMUINT4& xm);
  Vec2<T>& operator=(const DirectX::XMFLOAT2& xm);
  Vec2<T>& operator=(const DirectX::XMFLOAT3& xm);
  Vec2<T>& operator=(const DirectX::XMFLOAT4& xm);
  Vec2<T>& operator=(const DirectX::XMFLOAT2A& xm);
  Vec2<T>& operator=(const DirectX::XMFLOAT3A& xm);
  Vec2<T>& operator=(const DirectX::XMFLOAT4A& xm);
  Vec2<T>& operator=(const DirectX::XMVECTOR& xm);

  // Addition operators
  template <class U>
  Vec2<T> operator+(const U& v) const;
  template <class U>
  Vec2<T> operator+(const Vec2<U>& vec2) const;
  template <class U>
  Vec2<T> operator+(const Vec3<U>& vec3) const;
  template <class U>
  Vec2<T> operator+(const Vec4<U>& vec4) const;
  Vec2<T> operator+(const DirectX::XMINT2& xm) const;
  Vec2<T> operator+(const DirectX::XMINT3& xm) const;
  Vec2<T> operator+(const DirectX::XMINT4& xm) const;
  Vec2<T> operator+(const DirectX::XMUINT2& xm) const;
  Vec2<T> operator+(const DirectX::XMUINT3& xm) const;
  Vec2<T> operator+(const DirectX::XMUINT4& xm) const;
  Vec2<T> operator+(const DirectX::XMFLOAT2& xm) const;
  Vec2<T> operator+(const DirectX::XMFLOAT3& xm) const;
  Vec2<T> operator+(const DirectX::XMFLOAT4& xm) const;
  Vec2<T> operator+(const DirectX::XMFLOAT2A& xm) const;
  Vec2<T> operator+(const DirectX::XMFLOAT3A& xm) const;
  Vec2<T> operator+(const DirectX::XMFLOAT4A& xm) const;
  Vec2<T> operator+(const DirectX::XMVECTOR& xm) const;
  template <class U>
  Vec2<T>& operator+=(const U& v);
  template <class U>
  Vec2<T>& operator+=(const Vec2<U>& vec2);
  template <class U>
  Vec2<T>& operator+=(const Vec3<U>& vec3);
  template <class U>
  Vec2<T>& operator+=(const Vec4<U>& vec4);
  Vec2<T>& operator+=(const DirectX::XMINT2& xm);
  Vec2<T>& operator+=(const DirectX::XMINT3& xm);
  Vec2<T>& operator+=(const DirectX::XMINT4& xm);
  Vec2<T>& operator+=(const DirectX::XMUINT2& xm);
  Vec2<T>& operator+=(const DirectX::XMUINT3& xm);
  Vec2<T>& operator+=(const DirectX::XMUINT4& xm);
  Vec2<T>& operator+=(const DirectX::XMFLOAT2& xm);
  Vec2<T>& operator+=(const DirectX::XMFLOAT3& xm);
  Vec2<T>& operator+=(const DirectX::XMFLOAT4& xm);
  Vec2<T>& operator+=(const DirectX::XMFLOAT2A& xm);
  Vec2<T>& operator+=(const DirectX::XMFLOAT3A& xm);
  Vec2<T>& operator+=(const DirectX::XMFLOAT4A& xm);
  Vec2<T>& operator+=(const DirectX::XMVECTOR& xm);

  // Subtraction operators
  template <class U>
  Vec2<T> operator-(const U& v) const;
  template <class U>
  Vec2<T> operator-(const Vec2<U>& vec2) const;
  template <class U>
  Vec2<T> operator-(const Vec3<U>& vec3) const;
  template <class U>
  Vec2<T> operator-(const Vec4<U>& vec4) const;
  Vec2<T> operator-(const DirectX::XMINT2& xm) const;
  Vec2<T> operator-(const DirectX::XMINT3& xm) const;
  Vec2<T> operator-(const DirectX::XMINT4& xm) const;
  Vec2<T> operator-(const DirectX::XMUINT2& xm) const;
  Vec2<T> operator-(const DirectX::XMUINT3& xm) const;
  Vec2<T> operator-(const DirectX::XMUINT4& xm) const;
  Vec2<T> operator-(const DirectX::XMFLOAT2& xm) const;
  Vec2<T> operator-(const DirectX::XMFLOAT3& xm) const;
  Vec2<T> operator-(const DirectX::XMFLOAT4& xm) const;
  Vec2<T> operator-(const DirectX::XMFLOAT2A& xm) const;
  Vec2<T> operator-(const DirectX::XMFLOAT3A& xm) const;
  Vec2<T> operator-(const DirectX::XMFLOAT4A& xm) const;
  Vec2<T> operator-(const DirectX::XMVECTOR& xm) const;
  template <class U>
  Vec2<T>& operator-=(const U& v);
  template <class U>
  Vec2<T>& operator-=(const Vec2<U>& vec2);
  template <class U>
  Vec2<T>& operator-=(const Vec3<U>& vec3);
  template <class U>
  Vec2<T>& operator-=(const Vec4<U>& vec4);
  Vec2<T>& operator-=(const DirectX::XMINT2& xm);
  Vec2<T>& operator-=(const DirectX::XMINT3& xm);
  Vec2<T>& operator-=(const DirectX::XMINT4& xm);
  Vec2<T>& operator-=(const DirectX::XMUINT2& xm);
  Vec2<T>& operator-=(const DirectX::XMUINT3& xm);
  Vec2<T>& operator-=(const DirectX::XMUINT4& xm);
  Vec2<T>& operator-=(const DirectX::XMFLOAT2& xm);
  Vec2<T>& operator-=(const DirectX::XMFLOAT3& xm);
  Vec2<T>& operator-=(const DirectX::XMFLOAT4& xm);
  Vec2<T>& operator-=(const DirectX::XMFLOAT2A& xm);
  Vec2<T>& operator-=(const DirectX::XMFLOAT3A& xm);
  Vec2<T>& operator-=(const DirectX::XMFLOAT4A& xm);
  Vec2<T>& operator-=(const DirectX::XMVECTOR& xm);

  // Multiplication operators
  template <class U>
  Vec2<T> operator*(const U& v) const;
  template <class U>
  Vec2<T> operator*(const Vec2<U>& vec2) const;
  template <class U>
  Vec2<T> operator*(const Vec3<U>& vec3) const;
  template <class U>
  Vec2<T> operator*(const Vec4<U>& vec4) const;
  Vec2<T> operator*(const DirectX::XMINT2& xm) const;
  Vec2<T> operator*(const DirectX::XMINT3& xm) const;
  Vec2<T> operator*(const DirectX::XMINT4& xm) const;
  Vec2<T> operator*(const DirectX::XMUINT2& xm) const;
  Vec2<T> operator*(const DirectX::XMUINT3& xm) const;
  Vec2<T> operator*(const DirectX::XMUINT4& xm) const;
  Vec2<T> operator*(const DirectX::XMFLOAT2& xm) const;
  Vec2<T> operator*(const DirectX::XMFLOAT3& xm) const;
  Vec2<T> operator*(const DirectX::XMFLOAT4& xm) const;
  Vec2<T> operator*(const DirectX::XMFLOAT2A& xm) const;
  Vec2<T> operator*(const DirectX::XMFLOAT3A& xm) const;
  Vec2<T> operator*(const DirectX::XMFLOAT4A& xm) const;
  Vec2<T> operator*(const DirectX::XMVECTOR& xm) const;
  template <class U>
  Vec2<T>& operator*=(const U& v);
  template <class U>
  Vec2<T>& operator*=(const Vec2<U>& vec2);
  template <class U>
  Vec2<T>& operator*=(const Vec3<U>& vec3);
  template <class U>
  Vec2<T>& operator*=(const Vec4<U>& vec4);
  Vec2<T>& operator*=(const DirectX::XMINT2& xm);
  Vec2<T>& operator*=(const DirectX::XMINT3& xm);
  Vec2<T>& operator*=(const DirectX::XMINT4& xm);
  Vec2<T>& operator*=(const DirectX::XMUINT2& xm);
  Vec2<T>& operator*=(const DirectX::XMUINT3& xm);
  Vec2<T>& operator*=(const DirectX::XMUINT4& xm);
  Vec2<T>& operator*=(const DirectX::XMFLOAT2& xm);
  Vec2<T>& operator*=(const DirectX::XMFLOAT3& xm);
  Vec2<T>& operator*=(const DirectX::XMFLOAT4& xm);
  Vec2<T>& operator*=(const DirectX::XMFLOAT2A& xm);
  Vec2<T>& operator*=(const DirectX::XMFLOAT3A& xm);
  Vec2<T>& operator*=(const DirectX::XMFLOAT4A& xm);
  Vec2<T>& operator*=(const DirectX::XMVECTOR& xm);

  // Divition operators
  template <class U>
  Vec2<T> operator/(const U& v) const;
  template <class U>
  Vec2<T> operator/(const Vec2<U>& vec2) const;
  template <class U>
  Vec2<T> operator/(const Vec3<U>& vec3) const;
  template <class U>
  Vec2<T> operator/(const Vec4<U>& vec4) const;
  Vec2<T> operator/(const DirectX::XMINT2& xm) const;
  Vec2<T> operator/(const DirectX::XMINT3& xm) const;
  Vec2<T> operator/(const DirectX::XMINT4& xm) const;
  Vec2<T> operator/(const DirectX::XMUINT2& xm) const;
  Vec2<T> operator/(const DirectX::XMUINT3& xm) const;
  Vec2<T> operator/(const DirectX::XMUINT4& xm) const;
  Vec2<T> operator/(const DirectX::XMFLOAT2& xm) const;
  Vec2<T> operator/(const DirectX::XMFLOAT3& xm) const;
  Vec2<T> operator/(const DirectX::XMFLOAT4& xm) const;
  Vec2<T> operator/(const DirectX::XMFLOAT2A& xm) const;
  Vec2<T> operator/(const DirectX::XMFLOAT3A& xm) const;
  Vec2<T> operator/(const DirectX::XMFLOAT4A& xm) const;
  Vec2<T> operator/(const DirectX::XMVECTOR& xm) const;
  template <class U>
  Vec2<T>& operator/=(const U& v);
  template <class U>
  Vec2<T>& operator/=(const Vec2<U>& vec2);
  template <class U>
  Vec2<T>& operator/=(const Vec3<U>& vec3);
  template <class U>
  Vec2<T>& operator/=(const Vec4<U>& vec4);
  Vec2<T>& operator/=(const DirectX::XMINT2& xm);
  Vec2<T>& operator/=(const DirectX::XMINT3& xm);
  Vec2<T>& operator/=(const DirectX::XMINT4& xm);
  Vec2<T>& operator/=(const DirectX::XMUINT2& xm);
  Vec2<T>& operator/=(const DirectX::XMUINT3& xm);
  Vec2<T>& operator/=(const DirectX::XMUINT4& xm);
  Vec2<T>& operator/=(const DirectX::XMFLOAT2& xm);
  Vec2<T>& operator/=(const DirectX::XMFLOAT3& xm);
  Vec2<T>& operator/=(const DirectX::XMFLOAT4& xm);
  Vec2<T>& operator/=(const DirectX::XMFLOAT2A& xm);
  Vec2<T>& operator/=(const DirectX::XMFLOAT3A& xm);
  Vec2<T>& operator/=(const DirectX::XMFLOAT4A& xm);
  Vec2<T>& operator/=(const DirectX::XMVECTOR& xm);

  // Equal operators
  template <class U>
  bool operator==(const U& v) const;
  template <class U>
  bool operator==(const Vec2<U>& vec2) const;
  template <class U>
  bool operator==(const Vec3<U>& vec3) const;
  template <class U>
  bool operator==(const Vec4<U>& vec4) const;
  bool operator==(const DirectX::XMINT2& xm) const;
  bool operator==(const DirectX::XMINT3& xm) const;
  bool operator==(const DirectX::XMINT4& xm) const;
  bool operator==(const DirectX::XMUINT2& xm) const;
  bool operator==(const DirectX::XMUINT3& xm) const;
  bool operator==(const DirectX::XMUINT4& xm) const;
  bool operator==(const DirectX::XMFLOAT2& xm) const;
  bool operator==(const DirectX::XMFLOAT3& xm) const;
  bool operator==(const DirectX::XMFLOAT4& xm) const;
  bool operator==(const DirectX::XMFLOAT2A& xm) const;
  bool operator==(const DirectX::XMFLOAT3A& xm) const;
  bool operator==(const DirectX::XMFLOAT4A& xm) const;
  bool operator==(const DirectX::XMVECTOR& xm) const;

  // Bracket operator
  T& operator[](unsigned int i);
  T  operator[](unsigned int i) const;
#pragma endregion
#pragma region Functions
  DirectX::XMVECTOR  Load() const;
  void               Store(const DirectX::XMVECTOR& xm);
  T                  Length() const;
  T                  LengthSq() const;
  DirectX::XMINT2    AsXmInt2() const;
  DirectX::XMINT3    AsXmInt3(int z = 0) const;
  DirectX::XMINT4    AsXmInt4(int z = 0, int w = 0) const;
  DirectX::XMUINT2   AsXmUint2() const;
  DirectX::XMUINT3   AsXmUint3(unsigned int z = 0u) const;
  DirectX::XMUINT4   AsXmUint4(unsigned int z = 0u, unsigned int w = 0) const;
  DirectX::XMFLOAT2  AsXmFloat2() const;
  DirectX::XMFLOAT3  AsXmFloat3(float z = 0.0f) const;
  DirectX::XMFLOAT4  AsXmFloat4(float z = 0.0f, float w = 0.0f) const;
  DirectX::XMFLOAT2A AsXmAsXmFloat2A() const;
  DirectX::XMFLOAT3A AsXmAsXmFloat3A(float z = 0.0f) const;
  DirectX::XMFLOAT4A AsXmAsXmFloat4A(float z = 0.0f, float w = 0.0f) const;
  Vec2<T>            Abs() const;
  Vec2<T>            Normalize() const;
  template <class U>
  float       Dot(const Vec2<U>& vec2) const;
  float       Dot(const DirectX::XMINT2& xm) const;
  float       Dot(const DirectX::XMUINT2& xm) const;
  float       Dot(const DirectX::XMFLOAT2& xm) const;
  float       Dot(const DirectX::XMFLOAT2A& xm) const;
  std::string ToString() const;
#pragma endregion
public:
#pragma region Members
  union
  {
    struct
    {
      T x;
      union
      {
        T y;
        T z;
      };
    };
    T data[2];
  };
#pragma endregion
};
#include "../vec3/Vec3.h"
#include "../vec4/Vec4.h"
#pragma region Constructors
template <class T>
inline Vec2<T>::Vec2()
{
  x = static_cast<T>(0);
  y = static_cast<T>(0);
}

template <class T>
template <class U>
inline Vec2<T>::Vec2(U v)
{
  x = static_cast<T>(v);
  y = static_cast<T>(v);
}
template <class T>
template <class U, class V>
inline Vec2<T>::Vec2(U _x, V _y)
{
  x = static_cast<T>(_x);
  y = static_cast<T>(_y);
}

template <class T>
template <class U>
inline Vec2<T>::Vec2(const Vec2<U>& vec2)
{
  x = static_cast<T>(vec2.x);
  y = static_cast<T>(vec2.y);
}

template <class T>
template <class U>
inline Vec2<T>::Vec2(const Vec3<U>& vec3)
{
  x = static_cast<T>(vec3.x);
  y = static_cast<T>(vec3.y);
}

template <class T>
template <class U>
inline Vec2<T>::Vec2(const Vec4<U>& vec4)
{
  x = static_cast<T>(vec4.x);
  y = static_cast<T>(vec4.y);
}

template <class T>
inline Vec2<T>::Vec2(const DirectX::XMINT2& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
}

template <class T>
inline Vec2<T>::Vec2(const DirectX::XMINT3& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
}

template <class T>
inline Vec2<T>::Vec2(const DirectX::XMINT4& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
}

template <class T>
inline Vec2<T>::Vec2(const DirectX::XMUINT2& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
}

template <class T>
inline Vec2<T>::Vec2(const DirectX::XMUINT3& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
}

template <class T>
inline Vec2<T>::Vec2(const DirectX::XMUINT4& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
}

template <class T>
inline

    Vec2<T>::Vec2(const DirectX::XMFLOAT2& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
}

template <class T>
inline Vec2<T>::Vec2(const DirectX::XMFLOAT3& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
}

template <class T>
inline Vec2<T>::Vec2(const DirectX::XMFLOAT4& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
}

template <class T>
inline Vec2<T>::Vec2(const DirectX::XMFLOAT2A& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
}

template <class T>
inline Vec2<T>::Vec2(const DirectX::XMFLOAT3A& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
}

template <class T>
inline Vec2<T>::Vec2(const DirectX::XMFLOAT4A& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
}

template <class T>
inline Vec2<T>::Vec2(const DirectX::XMVECTOR& xm)
{
  x = static_cast<T>(DirectX::XMVectorGetX(xm));
  y = static_cast<T>(DirectX::XMVectorGetY(xm));
}
#pragma endregion
#pragma region VectorOperatiors
template <class T>
template <class U>
inline Vec2<T>& Vec2<T>::operator=(const U& v)
{
  x = static_cast<T>(v);
  y = static_cast<T>(v);
  return *this;
}
template <class T>
template <class U>
inline Vec2<T>& Vec2<T>::operator=(const Vec2<U>& vec2)
{
  x = static_cast<T>(vec2.x);
  y = static_cast<T>(vec2.y);
  return *this;
}
template <class T>
template <class U>
inline Vec2<T>& Vec2<T>::operator=(const Vec3<U>& vec3)
{
  x = static_cast<T>(vec3.x);
  y = static_cast<T>(vec3.y);
  return *this;
}
template <class T>
template <class U>
inline Vec2<T>& Vec2<T>::operator=(const Vec4<U>& vec4)
{
  x = static_cast<T>(vec4.x);
  y = static_cast<T>(vec4.y);
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator=(const DirectX::XMINT2& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator=(const DirectX::XMINT3& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator=(const DirectX::XMINT4& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator=(const DirectX::XMUINT2& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator=(const DirectX::XMUINT3& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator=(const DirectX::XMUINT4& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator=(const DirectX::XMFLOAT2& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator=(const DirectX::XMFLOAT3& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator=(const DirectX::XMFLOAT4& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator=(const DirectX::XMFLOAT2A& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator=(const DirectX::XMFLOAT3A& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator=(const DirectX::XMFLOAT4A& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator=(const DirectX::XMVECTOR& xm)
{
  x = static_cast<T>(DirectX::XMVectorGetX(xm));
  y = static_cast<T>(DirectX::XMVectorGetY(xm));
  return *this;
}
template <class T>
template <class U>
inline Vec2<T> Vec2<T>::operator+(const U& v) const
{
  Vec2<T> vec(x, y);
  vec.x += static_cast<T>(v);
  vec.y += static_cast<T>(v);
  return vec;
}
template <class T>
template <class U>
inline Vec2<T> Vec2<T>::operator+(const Vec2<U>& vec2) const
{
  Vec2<T> vec(x, y);
  vec.x += static_cast<T>(vec2.x);
  vec.y += static_cast<T>(vec2.y);
  return vec;
}
template <class T>
template <class U>
inline Vec2<T> Vec2<T>::operator+(const Vec3<U>& vec3) const
{
  Vec2<T> vec(x, y);
  vec.x += static_cast<T>(vec3.x);
  vec.y += static_cast<T>(vec3.y);
  return vec;
}
template <class T>
template <class U>
inline Vec2<T> Vec2<T>::operator+(const Vec4<U>& vec4) const
{
  Vec2<T> vec(x, y);
  vec.x += static_cast<T>(vec4.x);
  vec.y += static_cast<T>(vec4.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator+(const DirectX::XMINT2& xm) const
{
  Vec2<T> vec(x, y);
  vec.x += static_cast<T>(xm.x);
  vec.y += static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator+(const DirectX::XMINT3& xm) const
{
  Vec2<T> vec(x, y);
  vec.x += static_cast<T>(xm.x);
  vec.y += static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator+(const DirectX::XMINT4& xm) const
{
  Vec2<T> vec(x, y);
  vec.x += static_cast<T>(xm.x);
  vec.y += static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator+(const DirectX::XMUINT2& xm) const
{
  Vec2<T> vec(x, y);
  vec.x += static_cast<T>(xm.x);
  vec.y += static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator+(const DirectX::XMUINT3& xm) const
{
  Vec2<T> vec(x, y);
  vec.x += static_cast<T>(xm.x);
  vec.y += static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator+(const DirectX::XMUINT4& xm) const
{
  Vec2<T> vec(x, y);
  vec.x += static_cast<T>(xm.x);
  vec.y += static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator+(const DirectX::XMFLOAT2& xm) const
{
  Vec2<T> vec(x, y);
  vec.x += static_cast<T>(xm.x);
  vec.y += static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator+(const DirectX::XMFLOAT3& xm) const
{
  Vec2<T> vec(x, y);
  vec.x += static_cast<T>(xm.x);
  vec.y += static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator+(const DirectX::XMFLOAT4& xm) const
{
  Vec2<T> vec(x, y);
  vec.x += static_cast<T>(xm.x);
  vec.y += static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator+(const DirectX::XMFLOAT2A& xm) const
{
  Vec2<T> vec(x, y);
  vec.x += static_cast<T>(xm.x);
  vec.y += static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator+(const DirectX::XMFLOAT3A& xm) const
{
  Vec2<T> vec(x, y);
  vec.x += static_cast<T>(xm.x);
  vec.y += static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator+(const DirectX::XMFLOAT4A& xm) const
{
  Vec2<T> vec(x, y);
  vec.x += static_cast<T>(xm.x);
  vec.y += static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator+(const DirectX::XMVECTOR& xm) const
{
  Vec2<T> vec(x, y);
  vec.x += static_cast<T>(DirectX::XMVectorGetX(xm));
  vec.y += static_cast<T>(DirectX::XMVectorGetY(xm));
  return vec;
}
template <class T>
template <class U>
inline Vec2<T>& Vec2<T>::operator+=(const U& v)
{
  *this = *this + v;
  return *this;
}
template <class T>
template <class U>
inline Vec2<T>& Vec2<T>::operator+=(const Vec2<U>& vec2)
{
  *this = *this + vec2;
  return *this;
}
template <class T>
template <class U>
inline Vec2<T>& Vec2<T>::operator+=(const Vec3<U>& vec3)
{
  *this = *this + vec3;
  return *this;
}
template <class T>
template <class U>
inline Vec2<T>& Vec2<T>::operator+=(const Vec4<U>& vec4)
{
  *this = *this + vec4;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator+=(const DirectX::XMINT2& xm)
{
  *this = *this + xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator+=(const DirectX::XMINT3& xm)
{
  *this = *this + xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator+=(const DirectX::XMINT4& xm)
{
  *this = *this + xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator+=(const DirectX::XMUINT2& xm)
{
  *this = *this + xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator+=(const DirectX::XMUINT3& xm)
{
  *this = *this + xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator+=(const DirectX::XMUINT4& xm)
{
  *this = *this + xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator+=(const DirectX::XMFLOAT2& xm)
{
  *this = *this + xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator+=(const DirectX::XMFLOAT3& xm)
{
  *this = *this + xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator+=(const DirectX::XMFLOAT4& xm)
{
  *this = *this + xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator+=(const DirectX::XMFLOAT2A& xm)
{
  *this = *this + xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator+=(const DirectX::XMFLOAT3A& xm)
{
  *this = *this + xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator+=(const DirectX::XMFLOAT4A& xm)
{
  *this = *this + xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator+=(const DirectX::XMVECTOR& xm)
{
  *this = *this + xm;
  return *this;
}
template <class T>
template <class U>
inline Vec2<T> Vec2<T>::operator-(const U& v) const
{
  Vec2<T> vec(x, y);
  vec.x -= static_cast<T>(v);
  vec.y -= static_cast<T>(v);
  return vec;
}
template <class T>
template <class U>
inline Vec2<T> Vec2<T>::operator-(const Vec2<U>& vec2) const
{
  Vec2<T> vec(x, y);
  vec.x -= static_cast<T>(vec2.x);
  vec.y -= static_cast<T>(vec2.y);
  return vec;
}
template <class T>
template <class U>
inline Vec2<T> Vec2<T>::operator-(const Vec3<U>& vec3) const
{
  Vec2<T> vec(x, y);
  vec.x -= static_cast<T>(vec3.x);
  vec.y -= static_cast<T>(vec3.y);
  return vec;
}
template <class T>
template <class U>
inline Vec2<T> Vec2<T>::operator-(const Vec4<U>& vec4) const
{
  Vec2<T> vec(x, y);
  vec.x -= static_cast<T>(vec4.x);
  vec.y -= static_cast<T>(vec4.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator-(const DirectX::XMINT2& xm) const
{
  Vec2<T> vec(x, y);
  vec.x -= static_cast<T>(xm.x);
  vec.y -= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator-(const DirectX::XMINT3& xm) const
{
  Vec2<T> vec(x, y);
  vec.x -= static_cast<T>(xm.x);
  vec.y -= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator-(const DirectX::XMINT4& xm) const
{
  Vec2<T> vec(x, y);
  vec.x -= static_cast<T>(xm.x);
  vec.y -= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator-(const DirectX::XMUINT2& xm) const
{
  Vec2<T> vec(x, y);
  vec.x -= static_cast<T>(xm.x);
  vec.y -= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator-(const DirectX::XMUINT3& xm) const
{
  Vec2<T> vec(x, y);
  vec.x -= static_cast<T>(xm.x);
  vec.y -= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator-(const DirectX::XMUINT4& xm) const
{
  Vec2<T> vec(x, y);
  vec.x -= static_cast<T>(xm.x);
  vec.y -= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator-(const DirectX::XMFLOAT2& xm) const
{
  Vec2<T> vec(x, y);
  vec.x -= static_cast<T>(xm.x);
  vec.y -= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator-(const DirectX::XMFLOAT3& xm) const
{
  Vec2<T> vec(x, y);
  vec.x -= static_cast<T>(xm.x);
  vec.y -= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator-(const DirectX::XMFLOAT4& xm) const
{
  Vec2<T> vec(x, y);
  vec.x -= static_cast<T>(xm.x);
  vec.y -= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator-(const DirectX::XMFLOAT2A& xm) const
{
  Vec2<T> vec(x, y);
  vec.x -= static_cast<T>(xm.x);
  vec.y -= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator-(const DirectX::XMFLOAT3A& xm) const
{
  Vec2<T> vec(x, y);
  vec.x -= static_cast<T>(xm.x);
  vec.y -= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator-(const DirectX::XMFLOAT4A& xm) const
{
  Vec2<T> vec(x, y);
  vec.x -= static_cast<T>(xm.x);
  vec.y -= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator-(const DirectX::XMVECTOR& xm) const
{
  Vec2<T> vec(x, y);
  vec.x -= static_cast<T>(DirectX::XMVectorGetX(xm));
  vec.y -= static_cast<T>(DirectX::XMVectorGetY(xm));
  return vec;
}
template <class T>
template <class U>
inline Vec2<T>& Vec2<T>::operator-=(const U& v)
{
  *this = *this - v;
  return *this;
}
template <class T>
template <class U>
inline Vec2<T>& Vec2<T>::operator-=(const Vec2<U>& vec2)
{
  *this = *this - vec2;
  return *this;
}
template <class T>
template <class U>
inline Vec2<T>& Vec2<T>::operator-=(const Vec3<U>& vec3)
{
  *this = *this - vec3;
  return *this;
}
template <class T>
template <class U>
inline Vec2<T>& Vec2<T>::operator-=(const Vec4<U>& vec4)
{
  *this = *this - vec4;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator-=(const DirectX::XMINT2& xm)
{
  *this = *this - xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator-=(const DirectX::XMINT3& xm)
{
  *this = *this - xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator-=(const DirectX::XMINT4& xm)
{
  *this = *this - xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator-=(const DirectX::XMUINT2& xm)
{
  *this = *this - xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator-=(const DirectX::XMUINT3& xm)
{
  *this = *this - xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator-=(const DirectX::XMUINT4& xm)
{
  *this = *this - xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator-=(const DirectX::XMFLOAT2& xm)
{
  *this = *this - xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator-=(const DirectX::XMFLOAT3& xm)
{
  *this = *this - xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator-=(const DirectX::XMFLOAT4& xm)
{
  *this = *this - xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator-=(const DirectX::XMFLOAT2A& xm)
{
  *this = *this - xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator-=(const DirectX::XMFLOAT3A& xm)
{
  *this = *this - xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator-=(const DirectX::XMFLOAT4A& xm)
{
  *this = *this - xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator-=(const DirectX::XMVECTOR& xm)
{
  *this = *this - xm;
  return *this;
}
template <class T>
template <class U>
inline Vec2<T> Vec2<T>::operator*(const U& v) const
{
  Vec2<T> vec(x, y);
  vec.x *= static_cast<T>(v);
  vec.y *= static_cast<T>(v);
  return vec;
}
template <class T>
template <class U>
inline Vec2<T> Vec2<T>::operator*(const Vec2<U>& vec2) const
{
  Vec2<T> vec(x, y);
  vec.x *= static_cast<T>(vec2.x);
  vec.y *= static_cast<T>(vec2.y);
  return vec;
}
template <class T>
template <class U>
inline Vec2<T> Vec2<T>::operator*(const Vec3<U>& vec3) const
{
  Vec2<T> vec(x, y);
  vec.x *= static_cast<T>(vec3.x);
  vec.y *= static_cast<T>(vec3.y);
  return vec;
}
template <class T>
template <class U>
inline Vec2<T> Vec2<T>::operator*(const Vec4<U>& vec4) const
{
  Vec2<T> vec(x, y);
  vec.x *= static_cast<T>(vec4.x);
  vec.y *= static_cast<T>(vec4.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator*(const DirectX::XMINT2& xm) const
{
  Vec2<T> vec(x, y);
  vec.x *= static_cast<T>(xm.x);
  vec.y *= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator*(const DirectX::XMINT3& xm) const
{
  Vec2<T> vec(x, y);
  vec.x *= static_cast<T>(xm.x);
  vec.y *= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator*(const DirectX::XMINT4& xm) const
{
  Vec2<T> vec(x, y);
  vec.x *= static_cast<T>(xm.x);
  vec.y *= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator*(const DirectX::XMUINT2& xm) const
{
  Vec2<T> vec(x, y);
  vec.x *= static_cast<T>(xm.x);
  vec.y *= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator*(const DirectX::XMUINT3& xm) const
{
  Vec2<T> vec(x, y);
  vec.x *= static_cast<T>(xm.x);
  vec.y *= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator*(const DirectX::XMUINT4& xm) const
{
  Vec2<T> vec(x, y);
  vec.x *= static_cast<T>(xm.x);
  vec.y *= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator*(const DirectX::XMFLOAT2& xm) const
{
  Vec2<T> vec(x, y);
  vec.x *= static_cast<T>(xm.x);
  vec.y *= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator*(const DirectX::XMFLOAT3& xm) const
{
  Vec2<T> vec(x, y);
  vec.x *= static_cast<T>(xm.x);
  vec.y *= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator*(const DirectX::XMFLOAT4& xm) const
{
  Vec2<T> vec(x, y);
  vec.x *= static_cast<T>(xm.x);
  vec.y *= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator*(const DirectX::XMFLOAT2A& xm) const
{
  Vec2<T> vec(x, y);
  vec.x *= static_cast<T>(xm.x);
  vec.y *= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator*(const DirectX::XMFLOAT3A& xm) const
{
  Vec2<T> vec(x, y);
  vec.x *= static_cast<T>(xm.x);
  vec.y *= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator*(const DirectX::XMFLOAT4A& xm) const
{
  Vec2<T> vec(x, y);
  vec.x *= static_cast<T>(xm.x);
  vec.y *= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator*(const DirectX::XMVECTOR& xm) const
{
  Vec2<T> vec(x, y);
  vec.x *= static_cast<T>(DirectX::XMVectorGetX(xm));
  vec.y *= static_cast<T>(DirectX::XMVectorGetY(xm));
  return vec;
}
template <class T>
template <class U>
inline Vec2<T>& Vec2<T>::operator*=(const U& v)
{
  *this = *this * v;
  return *this;
}
template <class T>
template <class U>
inline Vec2<T>& Vec2<T>::operator*=(const Vec2<U>& vec2)
{
  *this = *this * vec2;
  return *this;
}
template <class T>
template <class U>
inline Vec2<T>& Vec2<T>::operator*=(const Vec3<U>& vec3)
{
  *this = *this * vec3;
  return *this;
}
template <class T>
template <class U>
inline Vec2<T>& Vec2<T>::operator*=(const Vec4<U>& vec4)
{
  *this = *this * vec4;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator*=(const DirectX::XMINT2& xm)
{
  *this = *this * xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator*=(const DirectX::XMINT3& xm)
{
  *this = *this * xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator*=(const DirectX::XMINT4& xm)
{
  *this = *this * xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator*=(const DirectX::XMUINT2& xm)
{
  *this = *this * xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator*=(const DirectX::XMUINT3& xm)
{
  *this = *this * xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator*=(const DirectX::XMUINT4& xm)
{
  *this = *this * xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator*=(const DirectX::XMFLOAT2& xm)
{
  *this = *this * xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator*=(const DirectX::XMFLOAT3& xm)
{
  *this = *this * xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator*=(const DirectX::XMFLOAT4& xm)
{
  *this = *this * xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator*=(const DirectX::XMFLOAT2A& xm)
{
  *this = *this * xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator*=(const DirectX::XMFLOAT3A& xm)
{
  *this = *this * xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator*=(const DirectX::XMFLOAT4A& xm)
{
  *this = *this * xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator*=(const DirectX::XMVECTOR& xm)
{
  *this = *this * xm;
  return *this;
}
template <class T>
template <class U>
inline Vec2<T> Vec2<T>::operator/(const U& v) const
{
  Vec2<T> vec(x, y);
  vec.x /= static_cast<T>(v);
  vec.y /= static_cast<T>(v);
  return vec;
}
template <class T>
template <class U>
inline Vec2<T> Vec2<T>::operator/(const Vec2<U>& vec2) const
{
  Vec2<T> vec(x, y);
  vec.x /= static_cast<T>(vec2.x);
  vec.y /= static_cast<T>(vec2.y);
  return vec;
}
template <class T>
template <class U>
inline Vec2<T> Vec2<T>::operator/(const Vec3<U>& vec3) const
{
  Vec2<T> vec(x, y);
  vec.x /= static_cast<T>(vec3.x);
  vec.y /= static_cast<T>(vec3.y);
  return vec;
}
template <class T>
template <class U>
inline Vec2<T> Vec2<T>::operator/(const Vec4<U>& vec4) const
{
  Vec2<T> vec(x, y);
  vec.x /= static_cast<T>(vec4.x);
  vec.y /= static_cast<T>(vec4.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator/(const DirectX::XMINT2& xm) const
{
  Vec2<T> vec(x, y);
  vec.x /= static_cast<T>(xm.x);
  vec.y /= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator/(const DirectX::XMINT3& xm) const
{
  Vec2<T> vec(x, y);
  vec.x /= static_cast<T>(xm.x);
  vec.y /= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator/(const DirectX::XMINT4& xm) const
{
  Vec2<T> vec(x, y);
  vec.x /= static_cast<T>(xm.x);
  vec.y /= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator/(const DirectX::XMUINT2& xm) const
{
  Vec2<T> vec(x, y);
  vec.x /= static_cast<T>(xm.x);
  vec.y /= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator/(const DirectX::XMUINT3& xm) const
{
  Vec2<T> vec(x, y);
  vec.x /= static_cast<T>(xm.x);
  vec.y /= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator/(const DirectX::XMUINT4& xm) const
{
  Vec2<T> vec(x, y);
  vec.x /= static_cast<T>(xm.x);
  vec.y /= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator/(const DirectX::XMFLOAT2& xm) const
{
  Vec2<T> vec(x, y);
  vec.x /= static_cast<T>(xm.x);
  vec.y /= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator/(const DirectX::XMFLOAT3& xm) const
{
  Vec2<T> vec(x, y);
  vec.x /= static_cast<T>(xm.x);
  vec.y /= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator/(const DirectX::XMFLOAT4& xm) const
{
  Vec2<T> vec(x, y);
  vec.x /= static_cast<T>(xm.x);
  vec.y /= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator/(const DirectX::XMFLOAT2A& xm) const
{
  Vec2<T> vec(x, y);
  vec.x /= static_cast<T>(xm.x);
  vec.y /= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator/(const DirectX::XMFLOAT3A& xm) const
{
  Vec2<T> vec(x, y);
  vec.x /= static_cast<T>(xm.x);
  vec.y /= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator/(const DirectX::XMFLOAT4A& xm) const
{
  Vec2<T> vec(x, y);
  vec.x /= static_cast<T>(xm.x);
  vec.y /= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec2<T> Vec2<T>::operator/(const DirectX::XMVECTOR& xm) const
{
  Vec2<T> vec(x, y);
  vec.x /= static_cast<T>(DirectX::XMVectorGetX(xm));
  vec.y /= static_cast<T>(DirectX::XMVectorGetY(xm));
  return vec;
}
template <class T>
template <class U>
inline Vec2<T>& Vec2<T>::operator/=(const U& v)
{
  *this = *this / v;
  return *this;
}
template <class T>
template <class U>
inline Vec2<T>& Vec2<T>::operator/=(const Vec2<U>& vec2)
{
  *this = *this / vec2;
  return *this;
}
template <class T>
template <class U>
inline Vec2<T>& Vec2<T>::operator/=(const Vec3<U>& vec3)
{
  *this = *this / vec3;
  return *this;
}
template <class T>
template <class U>
inline Vec2<T>& Vec2<T>::operator/=(const Vec4<U>& vec4)
{
  *this = *this / vec4;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator/=(const DirectX::XMINT2& xm)
{
  *this = *this / xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator/=(const DirectX::XMINT3& xm)
{
  *this = *this / xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator/=(const DirectX::XMINT4& xm)
{
  *this = *this / xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator/=(const DirectX::XMUINT2& xm)
{
  *this = *this / xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator/=(const DirectX::XMUINT3& xm)
{
  *this = *this / xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator/=(const DirectX::XMUINT4& xm)
{
  *this = *this / xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator/=(const DirectX::XMFLOAT2& xm)
{
  *this = *this / xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator/=(const DirectX::XMFLOAT3& xm)
{
  *this = *this / xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator/=(const DirectX::XMFLOAT4& xm)
{
  *this = *this / xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator/=(const DirectX::XMFLOAT2A& xm)
{
  *this = *this / xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator/=(const DirectX::XMFLOAT3A& xm)
{
  *this = *this / xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator/=(const DirectX::XMFLOAT4A& xm)
{
  *this = *this / xm;
  return *this;
}
template <class T>
inline Vec2<T>& Vec2<T>::operator/=(const DirectX::XMVECTOR& xm)
{
  *this = *this / xm;
  return *this;
}

template <class T>
template <class U>
inline bool Vec2<T>::operator==(const U& v) const
{
  return x == static_cast<T>(v) && y == static_cast<T>(v);
}
template <class T>
template <class U>
inline bool Vec2<T>::operator==(const Vec2<U>& vec2) const
{
  return x == static_cast<T>(vec2.x) && y == static_cast<T>(vec2.y);
}
template <class T>
template <class U>
inline bool Vec2<T>::operator==(const Vec3<U>& vec3) const
{
  return x == static_cast<T>(vec3.x) && y == static_cast<T>(vec3.y);
}
template <class T>
template <class U>
inline bool Vec2<T>::operator==(const Vec4<U>& vec4) const
{
  return x == static_cast<T>(vec4.x) && y == static_cast<T>(vec4.y);
}
template <class T>
inline bool Vec2<T>::operator==(const DirectX::XMINT2& xm) const
{
  return x == static_cast<T>(xm.x) && y == static_cast<T>(xm.y);
}
template <class T>
inline bool Vec2<T>::operator==(const DirectX::XMINT3& xm) const
{
  return x == static_cast<T>(xm.x) && y == static_cast<T>(xm.y);
}
template <class T>
inline bool Vec2<T>::operator==(const DirectX::XMINT4& xm) const
{
  return x == static_cast<T>(xm.x) && y == static_cast<T>(xm.y);
}
template <class T>
inline bool Vec2<T>::operator==(const DirectX::XMUINT2& xm) const
{
  return x == static_cast<T>(xm.x) && y == static_cast<T>(xm.y);
}
template <class T>
inline bool Vec2<T>::operator==(const DirectX::XMUINT3& xm) const
{
  return x == static_cast<T>(xm.x) && y == static_cast<T>(xm.y);
}
template <class T>
inline bool Vec2<T>::operator==(const DirectX::XMUINT4& xm) const
{
  return x == static_cast<T>(xm.x) && y == static_cast<T>(xm.y);
}
template <class T>
inline bool Vec2<T>::operator==(const DirectX::XMFLOAT2& xm) const
{
  return x == static_cast<T>(xm.x) && y == static_cast<T>(xm.y);
}
template <class T>
inline bool Vec2<T>::operator==(const DirectX::XMFLOAT3& xm) const
{
  return x == static_cast<T>(xm.x) && y == static_cast<T>(xm.y);
}
template <class T>
inline bool Vec2<T>::operator==(const DirectX::XMFLOAT4& xm) const
{
  return x == static_cast<T>(xm.x) && y == static_cast<T>(xm.y);
}
template <class T>
inline bool Vec2<T>::operator==(const DirectX::XMFLOAT2A& xm) const
{
  return x == static_cast<T>(xm.x) && y == static_cast<T>(xm.y);
}
template <class T>
inline bool Vec2<T>::operator==(const DirectX::XMFLOAT3A& xm) const
{
  return x == static_cast<T>(xm.x) && y == static_cast<T>(xm.y);
}
template <class T>
inline bool Vec2<T>::operator==(const DirectX::XMFLOAT4A& xm) const
{
  return x == static_cast<T>(xm.x) && y == static_cast<T>(xm.y);
}
template <class T>
inline bool Vec2<T>::operator==(const DirectX::XMVECTOR& xm) const
{
  return x == static_cast<T>(DirectX ::XMVectorGetX(xm)) &&
         y == static_cast<T>(DirectX ::XMVectorGetY(xm));
}

template <class T>
inline T& Vec2<T>::operator[](unsigned int i)
{
  return data[i];
}
template <class T>
inline T Vec2<T>::operator[](unsigned int i) const
{
  return data[i];
}
#pragma endregion
#pragma region Functions
template <class T>
inline DirectX::XMVECTOR Vec2<T>::Load() const
{
  DirectX::XMVECTOR v = DirectX::XMVectorZero();
  v = DirectX::XMVectorSetX(v, static_cast<float>(x));
  v = DirectX::XMVectorSetY(v, static_cast<float>(y));
  v = DirectX::XMVectorSetZ(v, static_cast<float>(0));
  v = DirectX::XMVectorSetW(v, static_cast<float>(0));
  return v;
}
template <class T>
inline void Vec2<T>::Store(const DirectX::XMVECTOR& xm)
{
  x = static_cast<T>(DirectX::XMVectorGetX(xm));
  y = static_cast<T>(DirectX::XMVectorGetY(xm));
}

template <class T>
inline T Vec2<T>::Length() const
{
  return static_cast<T>(DirectX::XMVectorGetX(DirectX::XMVector2Length(Load())));
}
template <class T>
inline T Vec2<T>::LengthSq() const
{
  return static_cast<T>(DirectX::XMVectorGetX(DirectX::XMVector2LengthSq(Load())));
}
template <class T>
inline DirectX::XMINT2 Vec2<T>::AsXmInt2() const
{
  DirectX::XMINT2 v {};
  v.x = static_cast<int>(x);
  v.y = static_cast<int>(y);
  return v;
}
template <class T>
inline DirectX::XMINT3 Vec2<T>::AsXmInt3(int z) const
{
  DirectX::XMINT3 v {};
  v.x = static_cast<int>(x);
  v.y = static_cast<int>(y);
  v.z = z;
  return v;
}
template <class T>
inline DirectX::XMINT4 Vec2<T>::AsXmInt4(int z, int w) const
{
  DirectX::XMINT4 v {};
  v.x = static_cast<int>(x);
  v.y = static_cast<int>(y);
  v.z = z;
  v.w = w;
  return v;
}
template <class T>
inline DirectX::XMUINT2 Vec2<T>::AsXmUint2() const
{
  DirectX::XMUINT2 v {};
  v.x = static_cast<unsigned int>(x);
  v.y = static_cast<unsigned int>(y);
  return v;
}
template <class T>
inline DirectX::XMUINT3 Vec2<T>::AsXmUint3(unsigned int z) const
{
  DirectX::XMUINT3 v {};
  v.x = static_cast<unsigned int>(x);
  v.y = static_cast<unsigned int>(y);
  v.z = z;
  return v;
}
template <class T>
inline DirectX::XMUINT4 Vec2<T>::AsXmUint4(unsigned int z, unsigned int w) const
{
  DirectX::XMUINT4 v {};
  v.x = static_cast<unsigned int>(x);
  v.y = static_cast<unsigned int>(y);
  v.z = z;
  v.w = w;
  return v;
}
template <class T>
inline DirectX::XMFLOAT2 Vec2<T>::AsXmFloat2() const
{
  DirectX::XMFLOAT2 v {};
  v.x = static_cast<float>(x);
  v.y = static_cast<float>(y);
  return v;
}
template <class T>
inline DirectX::XMFLOAT3 Vec2<T>::AsXmFloat3(float z) const
{
  DirectX::XMFLOAT3 v {};
  v.x = static_cast<float>(x);
  v.y = static_cast<float>(y);
  v.z = z;
  return v;
}
template <class T>
inline DirectX::XMFLOAT4 Vec2<T>::AsXmFloat4(float z, float w) const
{
  DirectX::XMFLOAT4 v {};
  v.x = static_cast<float>(x);
  v.y = static_cast<float>(y);
  v.z = z;
  v.w = w;
  return v;
}
template <class T>
inline DirectX::XMFLOAT2A Vec2<T>::AsXmAsXmFloat2A() const
{
  DirectX::XMFLOAT2A v {};
  v.x = static_cast<float>(x);
  v.y = static_cast<float>(y);
  return v;
}
template <class T>
inline DirectX::XMFLOAT3A Vec2<T>::AsXmAsXmFloat3A(float z) const
{
  DirectX::XMFLOAT3A v {};
  v.x = static_cast<float>(x);
  v.y = static_cast<float>(y);
  v.z = z;
  return v;
}
template <class T>
inline DirectX::XMFLOAT4A Vec2<T>::AsXmAsXmFloat4A(float z, float w) const
{
  DirectX::XMFLOAT4A v {};
  v.x = static_cast<float>(x);
  v.y = static_cast<float>(y);
  v.z = z;
  v.w = w;
  return v;
}
template <class T>
inline Vec2<T> Vec2<T>::Abs() const
{
  Vec2<T> v = DirectX::XMVectorAbs(Load());
  return v;
}
template <class T>
inline Vec2<T> Vec2<T>::Normalize() const
{
  T       length = Length();
  Vec2<T> v(x / length, y / length);
  return v;
}
template <class T>
template <class U>
inline float Vec2<T>::Dot(const Vec2<U>& vec2) const
{
  return DirectX::XMVectorGetX(DirectX::XMVector2Dot(Load(), vec2.Load()));
}
template <class T>
inline float Vec2<T>::Dot(const DirectX::XMINT2& xm) const
{
  return DirectX::XMVectorGetX(DirectX::XMVector2Dot(Load(), DirectX::XMLoadSInt2(&xm)));
}
template <class T>
inline float Vec2<T>::Dot(const DirectX::XMUINT2& xm) const
{
  return DirectX::XMVectorGetX(DirectX::XMVector2Dot(Load(), DirectX::XMLoadUInt2(&xm)));
}
template <class T>
inline float Vec2<T>::Dot(const DirectX::XMFLOAT2& xm) const
{
  return DirectX::XMVectorGetX(DirectX::XMVector2Dot(Load(), DirectX::XMLoadFloat2(&xm)));
}
template <class T>
inline float Vec2<T>::Dot(const DirectX::XMFLOAT2A& xm) const
{
  return DirectX::XMVectorGetX(DirectX::XMVector2Dot(Load(), DirectX::XMLoadFloat2A(&xm)));
}
template <class T>
inline std::string Vec2<T>::ToString() const
{
  std::stringstream ss;
    ss << "[" << x << " " << y << "]";
    return ss.str();
  return "";
}
namespace std
{
  template <class T>
  struct hash<Vec2<T>>
  {
    size_t operator()(const Vec2<T>& p) const
    {
      size_t h =
          std::hash<T>()(p.x) ^ std::hash<T>()(p.y);
      return h;
    }
  };
} // namespace std
#pragma endregion