#pragma once
#include <DirectXMath.h>
#include <cstddef>
#include <sstream>
#include <string>

#pragma region ForwardDeclarations
template <class U>
class Vec2;
template <class U>
class Vec3;
template <class U>
class Mat3x3;
template <class U>
class Mat4x4;
#pragma endregion
template <class T>
class Vec4
{
public:
#pragma region Constructors
  Vec4();
  template <class U>
  Vec4(U v);
  template <class U, class V, class M, class P>
  Vec4(U _x, V _y, M _z, P _w);
  template <class U>
  Vec4(const Vec2<U>& vec2);
  template <class U>
  Vec4(const Vec3<U>& vec3);
  template <class U>
  Vec4(const Vec4<U>& vec4);
  Vec4(const DirectX::XMINT2& xm);
  Vec4(const DirectX::XMINT3& xm);
  Vec4(const DirectX::XMINT4& xm);

  Vec4(const DirectX::XMUINT2& xm);
  Vec4(const DirectX::XMUINT3& xm);
  Vec4(const DirectX::XMUINT4& xm);

  Vec4(const DirectX::XMFLOAT2& xm);
  Vec4(const DirectX::XMFLOAT3& xm);
  Vec4(const DirectX::XMFLOAT4& xm);
  Vec4(const DirectX::XMFLOAT2A& xm);
  Vec4(const DirectX::XMFLOAT3A& xm);
  Vec4(const DirectX::XMFLOAT4A& xm);
  Vec4(const DirectX::XMVECTOR& xm);
#pragma endregion
#pragma region VectorOperatiors
  // Asignment Operators
  template <class U>
  Vec4<T>& operator=(const U& v);
  template <class U>
  Vec4<T>& operator=(const Vec2<U>& vec2);
  template <class U>
  Vec4<T>& operator=(const Vec3<U>& vec3);
  template <class U>
  Vec4<T>& operator=(const Vec4<U>& vec4);
  Vec4<T>& operator=(const DirectX::XMINT2& xm);
  Vec4<T>& operator=(const DirectX::XMINT3& xm);
  Vec4<T>& operator=(const DirectX::XMINT4& xm);
  Vec4<T>& operator=(const DirectX::XMUINT2& xm);
  Vec4<T>& operator=(const DirectX::XMUINT3& xm);
  Vec4<T>& operator=(const DirectX::XMUINT4& xm);
  Vec4<T>& operator=(const DirectX::XMFLOAT2& xm);
  Vec4<T>& operator=(const DirectX::XMFLOAT3& xm);
  Vec4<T>& operator=(const DirectX::XMFLOAT4& xm);
  Vec4<T>& operator=(const DirectX::XMFLOAT2A& xm);
  Vec4<T>& operator=(const DirectX::XMFLOAT3A& xm);
  Vec4<T>& operator=(const DirectX::XMFLOAT4A& xm);
  Vec4<T>& operator=(const DirectX::XMVECTOR& xm);

  // Addition operators
  template <class U>
  Vec4<T> operator+(const U& v) const;
  template <class U>
  Vec4<T> operator+(const Vec2<U>& vec2) const;
  template <class U>
  Vec4<T> operator+(const Vec3<U>& vec3) const;
  template <class U>
  Vec4<T> operator+(const Vec4<U>& vec4) const;
  Vec4<T> operator+(const DirectX::XMINT2& xm) const;
  Vec4<T> operator+(const DirectX::XMINT3& xm) const;
  Vec4<T> operator+(const DirectX::XMINT4& xm) const;
  Vec4<T> operator+(const DirectX::XMUINT2& xm) const;
  Vec4<T> operator+(const DirectX::XMUINT3& xm) const;
  Vec4<T> operator+(const DirectX::XMUINT4& xm) const;
  Vec4<T> operator+(const DirectX::XMFLOAT2& xm) const;
  Vec4<T> operator+(const DirectX::XMFLOAT3& xm) const;
  Vec4<T> operator+(const DirectX::XMFLOAT4& xm) const;
  Vec4<T> operator+(const DirectX::XMFLOAT2A& xm) const;
  Vec4<T> operator+(const DirectX::XMFLOAT3A& xm) const;
  Vec4<T> operator+(const DirectX::XMFLOAT4A& xm) const;
  Vec4<T> operator+(const DirectX::XMVECTOR& xm) const;
  template <class U>
  Vec4<T>& operator+=(const U& v);
  template <class U>
  Vec4<T>& operator+=(const Vec2<U>& vec2);
  template <class U>
  Vec4<T>& operator+=(const Vec3<U>& vec3);
  template <class U>
  Vec4<T>& operator+=(const Vec4<U>& vec4);
  Vec4<T>& operator+=(const DirectX::XMINT2& xm);
  Vec4<T>& operator+=(const DirectX::XMINT3& xm);
  Vec4<T>& operator+=(const DirectX::XMINT4& xm);
  Vec4<T>& operator+=(const DirectX::XMUINT2& xm);
  Vec4<T>& operator+=(const DirectX::XMUINT3& xm);
  Vec4<T>& operator+=(const DirectX::XMUINT4& xm);
  Vec4<T>& operator+=(const DirectX::XMFLOAT2& xm);
  Vec4<T>& operator+=(const DirectX::XMFLOAT3& xm);
  Vec4<T>& operator+=(const DirectX::XMFLOAT4& xm);
  Vec4<T>& operator+=(const DirectX::XMFLOAT2A& xm);
  Vec4<T>& operator+=(const DirectX::XMFLOAT3A& xm);
  Vec4<T>& operator+=(const DirectX::XMFLOAT4A& xm);
  Vec4<T>& operator+=(const DirectX::XMVECTOR& xm);

  // Subtraction operators
  template <class U>
  Vec4<T> operator-(const U& v) const;
  template <class U>
  Vec4<T> operator-(const Vec2<U>& vec2) const;
  template <class U>
  Vec4<T> operator-(const Vec3<U>& vec3) const;
  template <class U>
  Vec4<T> operator-(const Vec4<U>& vec4) const;
  Vec4<T> operator-(const DirectX::XMINT2& xm) const;
  Vec4<T> operator-(const DirectX::XMINT3& xm) const;
  Vec4<T> operator-(const DirectX::XMINT4& xm) const;
  Vec4<T> operator-(const DirectX::XMUINT2& xm) const;
  Vec4<T> operator-(const DirectX::XMUINT3& xm) const;
  Vec4<T> operator-(const DirectX::XMUINT4& xm) const;
  Vec4<T> operator-(const DirectX::XMFLOAT2& xm) const;
  Vec4<T> operator-(const DirectX::XMFLOAT3& xm) const;
  Vec4<T> operator-(const DirectX::XMFLOAT4& xm) const;
  Vec4<T> operator-(const DirectX::XMFLOAT2A& xm) const;
  Vec4<T> operator-(const DirectX::XMFLOAT3A& xm) const;
  Vec4<T> operator-(const DirectX::XMFLOAT4A& xm) const;
  Vec4<T> operator-(const DirectX::XMVECTOR& xm) const;
  template <class U>
  Vec4<T>& operator-=(const U& v);
  template <class U>
  Vec4<T>& operator-=(const Vec2<U>& vec2);
  template <class U>
  Vec4<T>& operator-=(const Vec3<U>& vec3);
  template <class U>
  Vec4<T>& operator-=(const Vec4<U>& vec4);
  Vec4<T>& operator-=(const DirectX::XMINT2& xm);
  Vec4<T>& operator-=(const DirectX::XMINT3& xm);
  Vec4<T>& operator-=(const DirectX::XMINT4& xm);
  Vec4<T>& operator-=(const DirectX::XMUINT2& xm);
  Vec4<T>& operator-=(const DirectX::XMUINT3& xm);
  Vec4<T>& operator-=(const DirectX::XMUINT4& xm);
  Vec4<T>& operator-=(const DirectX::XMFLOAT2& xm);
  Vec4<T>& operator-=(const DirectX::XMFLOAT3& xm);
  Vec4<T>& operator-=(const DirectX::XMFLOAT4& xm);
  Vec4<T>& operator-=(const DirectX::XMFLOAT2A& xm);
  Vec4<T>& operator-=(const DirectX::XMFLOAT3A& xm);
  Vec4<T>& operator-=(const DirectX::XMFLOAT4A& xm);
  Vec4<T>& operator-=(const DirectX::XMVECTOR& xm);

  // Multiplication operators
  template <class U>
  Vec4<T> operator*(const U& v) const;
  template <class U>
  Vec4<T> operator*(const Vec2<U>& vec2) const;
  template <class U>
  Vec4<T> operator*(const Vec3<U>& vec3) const;
  template <class U>
  Vec4<T> operator*(const Vec4<U>& vec4) const;
  Vec4<T> operator*(const DirectX::XMINT2& xm) const;
  Vec4<T> operator*(const DirectX::XMINT3& xm) const;
  Vec4<T> operator*(const DirectX::XMINT4& xm) const;
  Vec4<T> operator*(const DirectX::XMUINT2& xm) const;
  Vec4<T> operator*(const DirectX::XMUINT3& xm) const;
  Vec4<T> operator*(const DirectX::XMUINT4& xm) const;
  Vec4<T> operator*(const DirectX::XMFLOAT2& xm) const;
  Vec4<T> operator*(const DirectX::XMFLOAT3& xm) const;
  Vec4<T> operator*(const DirectX::XMFLOAT4& xm) const;
  Vec4<T> operator*(const DirectX::XMFLOAT2A& xm) const;
  Vec4<T> operator*(const DirectX::XMFLOAT3A& xm) const;
  Vec4<T> operator*(const DirectX::XMFLOAT4A& xm) const;
  Vec4<T> operator*(const DirectX::XMVECTOR& xm) const;
  template <class U>
  Vec4<T>& operator*=(const U& v);
  template <class U>
  Vec4<T>& operator*=(const Vec2<U>& vec2);
  template <class U>
  Vec4<T>& operator*=(const Vec3<U>& vec3);
  template <class U>
  Vec4<T>& operator*=(const Vec4<U>& vec4);
  Vec4<T>& operator*=(const DirectX::XMINT2& xm);
  Vec4<T>& operator*=(const DirectX::XMINT3& xm);
  Vec4<T>& operator*=(const DirectX::XMINT4& xm);
  Vec4<T>& operator*=(const DirectX::XMUINT2& xm);
  Vec4<T>& operator*=(const DirectX::XMUINT3& xm);
  Vec4<T>& operator*=(const DirectX::XMUINT4& xm);
  Vec4<T>& operator*=(const DirectX::XMFLOAT2& xm);
  Vec4<T>& operator*=(const DirectX::XMFLOAT3& xm);
  Vec4<T>& operator*=(const DirectX::XMFLOAT4& xm);
  Vec4<T>& operator*=(const DirectX::XMFLOAT2A& xm);
  Vec4<T>& operator*=(const DirectX::XMFLOAT3A& xm);
  Vec4<T>& operator*=(const DirectX::XMFLOAT4A& xm);
  Vec4<T>& operator*=(const DirectX::XMVECTOR& xm);

  // Divition operators
  template <class U>
  Vec4<T> operator/(const U& v) const;
  template <class U>
  Vec4<T> operator/(const Vec2<U>& vec2) const;
  template <class U>
  Vec4<T> operator/(const Vec3<U>& vec3) const;
  template <class U>
  Vec4<T> operator/(const Vec4<U>& vec4) const;
  Vec4<T> operator/(const DirectX::XMINT2& xm) const;
  Vec4<T> operator/(const DirectX::XMINT3& xm) const;
  Vec4<T> operator/(const DirectX::XMINT4& xm) const;
  Vec4<T> operator/(const DirectX::XMUINT2& xm) const;
  Vec4<T> operator/(const DirectX::XMUINT3& xm) const;
  Vec4<T> operator/(const DirectX::XMUINT4& xm) const;
  Vec4<T> operator/(const DirectX::XMFLOAT2& xm) const;
  Vec4<T> operator/(const DirectX::XMFLOAT3& xm) const;
  Vec4<T> operator/(const DirectX::XMFLOAT4& xm) const;
  Vec4<T> operator/(const DirectX::XMFLOAT2A& xm) const;
  Vec4<T> operator/(const DirectX::XMFLOAT3A& xm) const;
  Vec4<T> operator/(const DirectX::XMFLOAT4A& xm) const;
  Vec4<T> operator/(const DirectX::XMVECTOR& xm) const;
  template <class U>
  Vec4<T>& operator/=(const U& v);
  template <class U>
  Vec4<T>& operator/=(const Vec2<U>& vec2);
  template <class U>
  Vec4<T>& operator/=(const Vec3<U>& vec3);
  template <class U>
  Vec4<T>& operator/=(const Vec4<U>& vec4);
  Vec4<T>& operator/=(const DirectX::XMINT2& xm);
  Vec4<T>& operator/=(const DirectX::XMINT3& xm);
  Vec4<T>& operator/=(const DirectX::XMINT4& xm);
  Vec4<T>& operator/=(const DirectX::XMUINT2& xm);
  Vec4<T>& operator/=(const DirectX::XMUINT3& xm);
  Vec4<T>& operator/=(const DirectX::XMUINT4& xm);
  Vec4<T>& operator/=(const DirectX::XMFLOAT2& xm);
  Vec4<T>& operator/=(const DirectX::XMFLOAT3& xm);
  Vec4<T>& operator/=(const DirectX::XMFLOAT4& xm);
  Vec4<T>& operator/=(const DirectX::XMFLOAT2A& xm);
  Vec4<T>& operator/=(const DirectX::XMFLOAT3A& xm);
  Vec4<T>& operator/=(const DirectX::XMFLOAT4A& xm);
  Vec4<T>& operator/=(const DirectX::XMVECTOR& xm);

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
  T operator[](unsigned int i) const;
#pragma endregion
#pragma region MatrixOperators
  Vec4<T> operator*(const DirectX::XMMATRIX& mat) const;
  Vec4<T> operator*(const DirectX::XMFLOAT3X3 mat) const;
  Vec4<T> operator*(const DirectX::XMFLOAT4X4 mat) const;
  Vec4<T> operator*(const DirectX::XMFLOAT4X4A mat) const;
  template <class U>
  Vec4<T> operator*(const Mat3x3<U>& mat) const;
  template <class U>
  Vec4<T> operator*(const Mat4x4<U>& mat) const;

  Vec4<T>& operator*=(const DirectX::XMMATRIX& mat);
  Vec4<T>& operator*=(const DirectX::XMFLOAT3X3 mat);
  Vec4<T>& operator*=(const DirectX::XMFLOAT4X4 mat);
  Vec4<T>& operator*=(const DirectX::XMFLOAT4X4A mat);
  template <class U>
  Vec4<T>& operator*=(const Mat3x3<U>& mat);
  template <class U>
  Vec4<T>& operator*=(const Mat4x4<U>& mat);

#pragma endregion
#pragma region Functions
  DirectX::XMVECTOR  Load() const;
  void               Store(const DirectX::XMVECTOR& xm);
  T                  Length() const;
  T                  LengthSq() const;
  DirectX::XMINT2    AsXmInt2() const;
  DirectX::XMINT3    AsXmInt3() const;
  DirectX::XMINT4    AsXmInt4() const;
  DirectX::XMUINT2   AsXmUint2() const;
  DirectX::XMUINT3   AsXmUint3() const;
  DirectX::XMUINT4   AsXmUint4() const;
  DirectX::XMFLOAT2  AsXmFloat2() const;
  DirectX::XMFLOAT3  AsXmFloat3() const;
  DirectX::XMFLOAT4  AsXmFloat4() const;
  DirectX::XMFLOAT2A AsXmAsXmFloat2A() const;
  DirectX::XMFLOAT3A AsXmAsXmFloat3A() const;
  DirectX::XMFLOAT4A AsXmAsXmFloat4A() const;
  Vec4<T>            Abs() const;
  Vec4<T>            Normalize() const;
  template <class U>
  float       Dot(const Vec4<U>& Vec4) const;
  float       Dot(const DirectX::XMINT4& xm) const;
  float       Dot(const DirectX::XMUINT4& xm) const;
  float       Dot(const DirectX::XMFLOAT4& xm) const;
  float       Dot(const DirectX::XMFLOAT4A& xm) const;
  std::string ToString() const;
#pragma endregion
public:
#pragma region Members
  union
  {
    struct
    {
      T x;
      T y;
      T z;
      T w;
    };
    struct
    {
      T r;
      T g;
      T b;
      T a;
    };
    T data[4];
  };
#pragma endregion
};
#include "Mat3x3.h"
#include "Mat4x4.h"
#include "Vec2.h"
#include "Vec3.h"
#pragma region Constructors
template <class T>
inline Vec4<T>::Vec4()
{
  x = static_cast<T>(0);
  y = static_cast<T>(0);
  z = static_cast<T>(0);
  w = static_cast<T>(0);
}

template <class T>
template <class U>
inline Vec4<T>::Vec4(U v)
{
  x = static_cast<T>(v);
  y = static_cast<T>(v);
  z = static_cast<T>(v);
  w = static_cast<T>(v);
}
template <class T>
template <class U, class V, class M, class P>
inline Vec4<T>::Vec4(U _x, V _y, M _z, P _w)
{
  x = static_cast<T>(_x);
  y = static_cast<T>(_y);
  z = static_cast<T>(_z);
  w = static_cast<T>(_w);
}

template <class T>
template <class U>
inline Vec4<T>::Vec4(const Vec2<U>& vec2)
{
  x = static_cast<T>(vec2.x);
  y = static_cast<T>(vec2.y);
  z = static_cast<T>(0);
  w = static_cast<T>(0);
}

template <class T>
template <class U>
inline Vec4<T>::Vec4(const Vec3<U>& vec3)
{
  x = static_cast<T>(vec3.x);
  y = static_cast<T>(vec3.y);
  z = static_cast<T>(vec3.z);
  w = static_cast<T>(0);
}

template <class T>
template <class U>
inline Vec4<T>::Vec4(const Vec4<U>& vec4)
{
  x = static_cast<T>(vec4.x);
  y = static_cast<T>(vec4.y);
  z = static_cast<T>(vec4.z);
  w = static_cast<T>(vec4.w);
}

template <class T>
inline Vec4<T>::Vec4(const DirectX::XMINT2& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(0);
  w = static_cast<T>(0);
}

template <class T>
inline Vec4<T>::Vec4(const DirectX::XMINT3& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(xm.z);
  w = static_cast<T>(0);
}

template <class T>
inline Vec4<T>::Vec4(const DirectX::XMINT4& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(xm.z);
  w = static_cast<T>(xm.w);
}

template <class T>
inline Vec4<T>::Vec4(const DirectX::XMUINT2& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(0);
  w = static_cast<T>(0);
}

template <class T>
inline Vec4<T>::Vec4(const DirectX::XMUINT3& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(xm.z);
  w = static_cast<T>(0);
}

template <class T>
inline Vec4<T>::Vec4(const DirectX::XMUINT4& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(xm.z);
  w = static_cast<T>(xm.w);
}

template <class T>
inline Vec4<T>::Vec4(const DirectX::XMFLOAT2& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(0);
  w = static_cast<T>(0);
}

template <class T>
inline Vec4<T>::Vec4(const DirectX::XMFLOAT3& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(xm.z);
  w = static_cast<T>(0);
}

template <class T>
inline Vec4<T>::Vec4(const DirectX::XMFLOAT4& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(xm.z);
  w = static_cast<T>(xm.w);
}

template <class T>
inline Vec4<T>::Vec4(const DirectX::XMFLOAT2A& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(0);
  w = static_cast<T>(0);
}

template <class T>
inline Vec4<T>::Vec4(const DirectX::XMFLOAT3A& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(xm.z);
  w = static_cast<T>(0);
}

template <class T>
inline Vec4<T>::Vec4(const DirectX::XMFLOAT4A& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(xm.z);
  w = static_cast<T>(xm.w);
}

template <class T>
inline Vec4<T>::Vec4(const DirectX::XMVECTOR& xm)
{
  x = static_cast<T>(DirectX::XMVectorGetX(xm));
  y = static_cast<T>(DirectX::XMVectorGetY(xm));
  z = static_cast<T>(DirectX::XMVectorGetZ(xm));
  w = static_cast<T>(DirectX::XMVectorGetW(xm));
}
#pragma endregion
#pragma region VectorOperatiors
template <class T>
template <class U>
inline Vec4<T>& Vec4<T>::operator=(const U& v)
{
  x = static_cast<T>(v);
  y = static_cast<T>(v);
  z = static_cast<T>(v);
  w = static_cast<T>(w);
  return *this;
}
template <class T>
template <class U>
inline Vec4<T>& Vec4<T>::operator=(const Vec2<U>& vec2)
{
  x = static_cast<T>(vec2.x);
  y = static_cast<T>(vec2.y);
  z = static_cast<T>(0);
  w = static_cast<T>(0);
  return *this;
}
template <class T>
template <class U>
inline Vec4<T>& Vec4<T>::operator=(const Vec3<U>& vec3)
{
  x = static_cast<T>(vec3.x);
  y = static_cast<T>(vec3.y);
  z = static_cast<T>(vec3.z);
  w = static_cast<T>(0);
  return *this;
}
template <class T>
template <class U>
inline Vec4<T>& Vec4<T>::operator=(const Vec4<U>& vec4)
{
  x = static_cast<T>(vec4.x);
  y = static_cast<T>(vec4.y);
  z = static_cast<T>(vec4.z);
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator=(const DirectX::XMINT2& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(0);
  w = static_cast<T>(0);
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator=(const DirectX::XMINT3& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(xm.z);
  w = static_cast<T>(0);
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator=(const DirectX::XMINT4& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(xm.z);
  w = static_cast<T>(xm.w);
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator=(const DirectX::XMUINT2& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(0);
  w = static_cast<T>(0);
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator=(const DirectX::XMUINT3& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(xm.z);
  w = static_cast<T>(0);
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator=(const DirectX::XMUINT4& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(xm.z);
  w = static_cast<T>(xm.w);
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator=(const DirectX::XMFLOAT2& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(0);
  w = static_cast<T>(0);
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator=(const DirectX::XMFLOAT3& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(xm.z);
  w = static_cast<T>(0);
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator=(const DirectX::XMFLOAT4& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(xm.z);
  w = static_cast<T>(xm.w);
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator=(const DirectX::XMFLOAT2A& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(0);
  w = static_cast<T>(0);
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator=(const DirectX::XMFLOAT3A& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(xm.z);
  w = static_cast<T>(0);
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator=(const DirectX::XMFLOAT4A& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(xm.z);
  w = static_cast<T>(xm.w);
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator=(const DirectX::XMVECTOR& xm)
{
  x = static_cast<T>(DirectX::XMVectorGetX(xm));
  y = static_cast<T>(DirectX::XMVectorGetY(xm));
  z = static_cast<T>(DirectX::XMVectorGetZ(xm));
  w = static_cast<T>(DirectX::XMVectorGetW(xm));
  return *this;
}
template <class T>
template <class U>
inline Vec4<T> Vec4<T>::operator+(const U& v) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x += static_cast<T>(v);
  vec.y += static_cast<T>(v);
  vec.z += static_cast<T>(v);
  vec.w += static_cast<T>(v);
  return vec;
}
template <class T>
template <class U>
inline Vec4<T> Vec4<T>::operator+(const Vec2<U>& vec2) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x += static_cast<T>(vec2.x);
  vec.y += static_cast<T>(vec2.y);
  vec.z += static_cast<T>(0);
  vec.w += static_cast<T>(0);
  return vec;
}
template <class T>
template <class U>
inline Vec4<T> Vec4<T>::operator+(const Vec3<U>& vec3) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x += static_cast<T>(vec3.x);
  vec.y += static_cast<T>(vec3.y);
  vec.z += static_cast<T>(vec3.z);
  vec.w += static_cast<T>(0);
  return vec;
}
template <class T>
template <class U>
inline Vec4<T> Vec4<T>::operator+(const Vec4<U>& vec4) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x += static_cast<T>(vec4.x);
  vec.y += static_cast<T>(vec4.y);
  vec.z += static_cast<T>(vec4.z);
  vec.w += static_cast<T>(vec4.w);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator+(const DirectX::XMINT2& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x += static_cast<T>(xm.x);
  vec.y += static_cast<T>(xm.y);
  vec.z += static_cast<T>(0);
  vec.w += static_cast<T>(0);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator+(const DirectX::XMINT3& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x += static_cast<T>(xm.x);
  vec.y += static_cast<T>(xm.y);
  vec.z += static_cast<T>(xm.z);
  vec.w += static_cast<T>(0);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator+(const DirectX::XMINT4& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x += static_cast<T>(xm.x);
  vec.y += static_cast<T>(xm.y);
  vec.z += static_cast<T>(xm.z);
  vec.w += static_cast<T>(xm.w);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator+(const DirectX::XMUINT2& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x += static_cast<T>(xm.x);
  vec.y += static_cast<T>(xm.y);
  vec.z += static_cast<T>(0);
  vec.w += static_cast<T>(0);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator+(const DirectX::XMUINT3& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x += static_cast<T>(xm.x);
  vec.y += static_cast<T>(xm.y);
  vec.z += static_cast<T>(xm.z);
  vec.w += static_cast<T>(0);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator+(const DirectX::XMUINT4& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x += static_cast<T>(xm.x);
  vec.y += static_cast<T>(xm.y);
  vec.z += static_cast<T>(xm.z);
  vec.w += static_cast<T>(xm.w);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator+(const DirectX::XMFLOAT2& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x += static_cast<T>(xm.x);
  vec.y += static_cast<T>(xm.y);
  vec.z += static_cast<T>(0);
  vec.w += static_cast<T>(0);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator+(const DirectX::XMFLOAT3& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x += static_cast<T>(xm.x);
  vec.y += static_cast<T>(xm.y);
  vec.z += static_cast<T>(xm.z);
  vec.w += static_cast<T>(0);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator+(const DirectX::XMFLOAT4& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x += static_cast<T>(xm.x);
  vec.y += static_cast<T>(xm.y);
  vec.z += static_cast<T>(xm.z);
  vec.w += static_cast<T>(xm.w);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator+(const DirectX::XMFLOAT2A& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x += static_cast<T>(xm.x);
  vec.y += static_cast<T>(xm.y);
  vec.z += static_cast<T>(0);
  vec.w += static_cast<T>(0);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator+(const DirectX::XMFLOAT3A& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x += static_cast<T>(xm.x);
  vec.y += static_cast<T>(xm.y);
  vec.z += static_cast<T>(xm.z);
  vec.w += static_cast<T>(0);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator+(const DirectX::XMFLOAT4A& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x += static_cast<T>(xm.x);
  vec.y += static_cast<T>(xm.y);
  vec.z += static_cast<T>(xm.z);
  vec.w += static_cast<T>(xm.w);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator+(const DirectX::XMVECTOR& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x += static_cast<T>(DirectX::XMVectorGetX(xm));
  vec.y += static_cast<T>(DirectX::XMVectorGetY(xm));
  vec.z += static_cast<T>(DirectX::XMVectorGetZ(xm));
  vec.w += static_cast<T>(DirectX::XMVectorGetW(xm));
  return vec;
}
template <class T>
template <class U>
inline Vec4<T>& Vec4<T>::operator+=(const U& v)
{
  *this = *this + v;
  return *this;
}
template <class T>
template <class U>
inline Vec4<T>& Vec4<T>::operator+=(const Vec2<U>& vec2)
{
  *this = *this + vec2;
  return *this;
}
template <class T>
template <class U>
inline Vec4<T>& Vec4<T>::operator+=(const Vec3<U>& vec3)
{
  *this = *this + vec3;
  return *this;
}
template <class T>
template <class U>
inline Vec4<T>& Vec4<T>::operator+=(const Vec4<U>& vec4)
{
  *this = *this + vec4;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator+=(const DirectX::XMINT2& xm)
{
  *this = *this + xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator+=(const DirectX::XMINT3& xm)
{
  *this = *this + xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator+=(const DirectX::XMINT4& xm)
{
  *this = *this + xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator+=(const DirectX::XMUINT2& xm)
{
  *this = *this + xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator+=(const DirectX::XMUINT3& xm)
{
  *this = *this + xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator+=(const DirectX::XMUINT4& xm)
{
  *this = *this + xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator+=(const DirectX::XMFLOAT2& xm)
{
  *this = *this + xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator+=(const DirectX::XMFLOAT3& xm)
{
  *this = *this + xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator+=(const DirectX::XMFLOAT4& xm)
{
  *this = *this + xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator+=(const DirectX::XMFLOAT2A& xm)
{
  *this = *this + xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator+=(const DirectX::XMFLOAT3A& xm)
{
  *this = *this + xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator+=(const DirectX::XMFLOAT4A& xm)
{
  *this = *this + xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator+=(const DirectX::XMVECTOR& xm)
{
  *this = *this + xm;
  return *this;
}
template <class T>
template <class U>
inline Vec4<T> Vec4<T>::operator-(const U& v) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x -= static_cast<T>(v);
  vec.y -= static_cast<T>(v);
  vec.z -= static_cast<T>(v);
  vec.w -= static_cast<T>(v);
  return vec;
}
template <class T>
template <class U>
inline Vec4<T> Vec4<T>::operator-(const Vec2<U>& vec2) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x -= static_cast<T>(vec2.x);
  vec.y -= static_cast<T>(vec2.y);
  vec.z -= static_cast<T>(0);
  vec.w -= static_cast<T>(0);
  return vec;
}
template <class T>
template <class U>
inline Vec4<T> Vec4<T>::operator-(const Vec3<U>& vec3) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x -= static_cast<T>(vec3.x);
  vec.y -= static_cast<T>(vec3.y);
  vec.z -= static_cast<T>(vec3.z);
  vec.w -= static_cast<T>(0);
  return vec;
}
template <class T>
template <class U>
inline Vec4<T> Vec4<T>::operator-(const Vec4<U>& vec4) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x -= static_cast<T>(vec4.x);
  vec.y -= static_cast<T>(vec4.y);
  vec.z -= static_cast<T>(vec4.z);
  vec.w -= static_cast<T>(vec4.w);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator-(const DirectX::XMINT2& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x -= static_cast<T>(xm.x);
  vec.y -= static_cast<T>(xm.y);
  vec.z -= static_cast<T>(0);
  vec.w -= static_cast<T>(0);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator-(const DirectX::XMINT3& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x -= static_cast<T>(xm.x);
  vec.y -= static_cast<T>(xm.y);
  vec.z -= static_cast<T>(xm.z);
  vec.w -= static_cast<T>(0);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator-(const DirectX::XMINT4& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x -= static_cast<T>(xm.x);
  vec.y -= static_cast<T>(xm.y);
  vec.z -= static_cast<T>(xm.z);
  vec.w -= static_cast<T>(xm.w);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator-(const DirectX::XMUINT2& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x -= static_cast<T>(xm.x);
  vec.y -= static_cast<T>(xm.y);
  vec.z -= static_cast<T>(0);
  vec.w -= static_cast<T>(0);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator-(const DirectX::XMUINT3& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x -= static_cast<T>(xm.x);
  vec.y -= static_cast<T>(xm.y);
  vec.z -= static_cast<T>(xm.z);
  vec.w -= static_cast<T>(0);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator-(const DirectX::XMUINT4& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x -= static_cast<T>(xm.x);
  vec.y -= static_cast<T>(xm.y);
  vec.z -= static_cast<T>(xm.z);
  vec.w -= static_cast<T>(xm.w);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator-(const DirectX::XMFLOAT2& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x -= static_cast<T>(xm.x);
  vec.y -= static_cast<T>(xm.y);
  vec.z -= static_cast<T>(0);
  vec.w -= static_cast<T>(0);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator-(const DirectX::XMFLOAT3& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x -= static_cast<T>(xm.x);
  vec.y -= static_cast<T>(xm.y);
  vec.z -= static_cast<T>(xm.z);
  vec.w -= static_cast<T>(0);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator-(const DirectX::XMFLOAT4& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x -= static_cast<T>(xm.x);
  vec.y -= static_cast<T>(xm.y);
  vec.z -= static_cast<T>(xm.z);
  vec.w -= static_cast<T>(xm.w);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator-(const DirectX::XMFLOAT2A& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x -= static_cast<T>(xm.x);
  vec.y -= static_cast<T>(xm.y);
  vec.z -= static_cast<T>(0);
  vec.w -= static_cast<T>(0);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator-(const DirectX::XMFLOAT3A& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x -= static_cast<T>(xm.x);
  vec.y -= static_cast<T>(xm.y);
  vec.z -= static_cast<T>(xm.z);
  vec.w -= static_cast<T>(0);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator-(const DirectX::XMFLOAT4A& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x -= static_cast<T>(xm.x);
  vec.y -= static_cast<T>(xm.y);
  vec.z -= static_cast<T>(xm.z);
  vec.w -= static_cast<T>(xm.w);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator-(const DirectX::XMVECTOR& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x -= static_cast<T>(DirectX::XMVectorGetX(xm));
  vec.y -= static_cast<T>(DirectX::XMVectorGetY(xm));
  vec.z -= static_cast<T>(DirectX::XMVectorGetZ(xm));
  vec.w -= static_cast<T>(DirectX::XMVectorGetW(xm));
  return vec;
}
template <class T>
template <class U>
inline Vec4<T>& Vec4<T>::operator-=(const U& v)
{
  *this = *this - v;
  return *this;
}
template <class T>
template <class U>
inline Vec4<T>& Vec4<T>::operator-=(const Vec2<U>& vec2)
{
  *this = *this - vec2;
  return *this;
}
template <class T>
template <class U>
inline Vec4<T>& Vec4<T>::operator-=(const Vec3<U>& vec3)
{
  *this = *this - vec3;
  return *this;
}
template <class T>
template <class U>
inline Vec4<T>& Vec4<T>::operator-=(const Vec4<U>& vec4)
{
  *this = *this - vec4;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator-=(const DirectX::XMINT2& xm)
{
  *this = *this - xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator-=(const DirectX::XMINT3& xm)
{
  *this = *this - xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator-=(const DirectX::XMINT4& xm)
{
  *this = *this - xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator-=(const DirectX::XMUINT2& xm)
{
  *this = *this - xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator-=(const DirectX::XMUINT3& xm)
{
  *this = *this - xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator-=(const DirectX::XMUINT4& xm)
{
  *this = *this - xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator-=(const DirectX::XMFLOAT2& xm)
{
  *this = *this - xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator-=(const DirectX::XMFLOAT3& xm)
{
  *this = *this - xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator-=(const DirectX::XMFLOAT4& xm)
{
  *this = *this - xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator-=(const DirectX::XMFLOAT2A& xm)
{
  *this = *this - xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator-=(const DirectX::XMFLOAT3A& xm)
{
  *this = *this - xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator-=(const DirectX::XMFLOAT4A& xm)
{
  *this = *this - xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator-=(const DirectX::XMVECTOR& xm)
{
  *this = *this - xm;
  return *this;
}
template <class T>
template <class U>
inline Vec4<T> Vec4<T>::operator*(const U& v) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x *= static_cast<T>(v);
  vec.y *= static_cast<T>(v);
  vec.z *= static_cast<T>(v);
  vec.w *= static_cast<T>(v);
  return vec;
}
template <class T>
template <class U>
inline Vec4<T> Vec4<T>::operator*(const Vec2<U>& vec2) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x *= static_cast<T>(vec2.x);
  vec.y *= static_cast<T>(vec2.y);
  vec.z *= static_cast<T>(0);
  vec.w *= static_cast<T>(0);
  return vec;
}
template <class T>
template <class U>
inline Vec4<T> Vec4<T>::operator*(const Vec3<U>& vec3) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x *= static_cast<T>(vec3.x);
  vec.y *= static_cast<T>(vec3.y);
  vec.z *= static_cast<T>(vec3.z);
  vec.w *= static_cast<T>(0);
  return vec;
}
template <class T>
template <class U>
inline Vec4<T> Vec4<T>::operator*(const Vec4<U>& vec4) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x *= static_cast<T>(vec4.x);
  vec.y *= static_cast<T>(vec4.y);
  vec.z *= static_cast<T>(vec4.z);
  vec.w *= static_cast<T>(vec4.w);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator*(const DirectX::XMINT2& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x *= static_cast<T>(xm.x);
  vec.y *= static_cast<T>(xm.y);
  vec.z *= static_cast<T>(0);
  vec.w *= static_cast<T>(0);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator*(const DirectX::XMINT3& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x *= static_cast<T>(xm.x);
  vec.y *= static_cast<T>(xm.y);
  vec.z *= static_cast<T>(xm.z);
  vec.w *= static_cast<T>(0);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator*(const DirectX::XMINT4& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x *= static_cast<T>(xm.x);
  vec.y *= static_cast<T>(xm.y);
  vec.z *= static_cast<T>(xm.z);
  vec.w *= static_cast<T>(xm.w);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator*(const DirectX::XMUINT2& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x *= static_cast<T>(xm.x);
  vec.y *= static_cast<T>(xm.y);
  vec.z *= static_cast<T>(0);
  vec.w *= static_cast<T>(0);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator*(const DirectX::XMUINT3& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x *= static_cast<T>(xm.x);
  vec.y *= static_cast<T>(xm.y);
  vec.z *= static_cast<T>(xm.z);
  vec.w *= static_cast<T>(0);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator*(const DirectX::XMUINT4& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x *= static_cast<T>(xm.x);
  vec.y *= static_cast<T>(xm.y);
  vec.z *= static_cast<T>(xm.z);
  vec.w *= static_cast<T>(xm.w);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator*(const DirectX::XMFLOAT2& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x *= static_cast<T>(xm.x);
  vec.y *= static_cast<T>(xm.y);
  vec.z *= static_cast<T>(0);
  vec.w *= static_cast<T>(0);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator*(const DirectX::XMFLOAT3& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x *= static_cast<T>(xm.x);
  vec.y *= static_cast<T>(xm.y);
  vec.z *= static_cast<T>(xm.z);
  vec.w *= static_cast<T>(0);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator*(const DirectX::XMFLOAT4& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x *= static_cast<T>(xm.x);
  vec.y *= static_cast<T>(xm.y);
  vec.z *= static_cast<T>(xm.z);
  vec.w *= static_cast<T>(xm.w);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator*(const DirectX::XMFLOAT2A& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x *= static_cast<T>(xm.x);
  vec.y *= static_cast<T>(xm.y);
  vec.z *= static_cast<T>(0);
  vec.w *= static_cast<T>(0);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator*(const DirectX::XMFLOAT3A& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x *= static_cast<T>(xm.x);
  vec.y *= static_cast<T>(xm.y);
  vec.z *= static_cast<T>(xm.z);
  vec.w *= static_cast<T>(0);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator*(const DirectX::XMFLOAT4A& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x *= static_cast<T>(xm.x);
  vec.y *= static_cast<T>(xm.y);
  vec.z *= static_cast<T>(xm.z);
  vec.w *= static_cast<T>(xm.w);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator*(const DirectX::XMVECTOR& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x *= static_cast<T>(DirectX::XMVectorGetX(xm));
  vec.y *= static_cast<T>(DirectX::XMVectorGetY(xm));
  vec.z *= static_cast<T>(DirectX::XMVectorGetZ(xm));
  vec.w *= static_cast<T>(DirectX::XMVectorGetW(xm));
  return vec;
}
template <class T>
template <class U>
inline Vec4<T>& Vec4<T>::operator*=(const U& v)
{
  *this = *this * v;
  return *this;
}
template <class T>
template <class U>
inline Vec4<T>& Vec4<T>::operator*=(const Vec2<U>& vec2)
{
  *this = *this * vec2;
  return *this;
}
template <class T>
template <class U>
inline Vec4<T>& Vec4<T>::operator*=(const Vec3<U>& vec3)
{
  *this = *this * vec3;
  return *this;
}
template <class T>
template <class U>
inline Vec4<T>& Vec4<T>::operator*=(const Vec4<U>& vec4)
{
  *this = *this * vec4;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator*=(const DirectX::XMINT2& xm)
{
  *this = *this * xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator*=(const DirectX::XMINT3& xm)
{
  *this = *this * xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator*=(const DirectX::XMINT4& xm)
{
  *this = *this * xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator*=(const DirectX::XMUINT2& xm)
{
  *this = *this * xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator*=(const DirectX::XMUINT3& xm)
{
  *this = *this * xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator*=(const DirectX::XMUINT4& xm)
{
  *this = *this * xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator*=(const DirectX::XMFLOAT2& xm)
{
  *this = *this * xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator*=(const DirectX::XMFLOAT3& xm)
{
  *this = *this * xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator*=(const DirectX::XMFLOAT4& xm)
{
  *this = *this * xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator*=(const DirectX::XMFLOAT2A& xm)
{
  *this = *this * xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator*=(const DirectX::XMFLOAT3A& xm)
{
  *this = *this * xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator*=(const DirectX::XMFLOAT4A& xm)
{
  *this = *this * xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator*=(const DirectX::XMVECTOR& xm)
{
  *this = *this * xm;
  return *this;
}
template <class T>
template <class U>
inline Vec4<T> Vec4<T>::operator/(const U& v) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x /= static_cast<T>(v);
  vec.y /= static_cast<T>(v);
  vec.z /= static_cast<T>(v);
  vec.w /= static_cast<T>(v);
  return vec;
}
template <class T>
template <class U>
inline Vec4<T> Vec4<T>::operator/(const Vec2<U>& vec2) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x /= static_cast<T>(vec2.x);
  vec.y /= static_cast<T>(vec2.y);
  return vec;
}
template <class T>
template <class U>
inline Vec4<T> Vec4<T>::operator/(const Vec3<U>& vec3) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x /= static_cast<T>(vec3.x);
  vec.y /= static_cast<T>(vec3.y);
  vec.z /= static_cast<T>(vec3.z);
  return vec;
}
template <class T>
template <class U>
inline Vec4<T> Vec4<T>::operator/(const Vec4<U>& vec4) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x /= static_cast<T>(vec4.x);
  vec.y /= static_cast<T>(vec4.y);
  vec.z /= static_cast<T>(vec4.z);
  vec.w /= static_cast<T>(vec4.w);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator/(const DirectX::XMINT2& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x /= static_cast<T>(xm.x);
  vec.y /= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator/(const DirectX::XMINT3& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x /= static_cast<T>(xm.x);
  vec.y /= static_cast<T>(xm.y);
  vec.z /= static_cast<T>(xm.z);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator/(const DirectX::XMINT4& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x /= static_cast<T>(xm.x);
  vec.y /= static_cast<T>(xm.y);
  vec.z /= static_cast<T>(xm.z);
  vec.w /= static_cast<T>(xm.w);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator/(const DirectX::XMUINT2& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x /= static_cast<T>(xm.x);
  vec.y /= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator/(const DirectX::XMUINT3& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x /= static_cast<T>(xm.x);
  vec.y /= static_cast<T>(xm.y);
  vec.z /= static_cast<T>(xm.z);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator/(const DirectX::XMUINT4& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x /= static_cast<T>(xm.x);
  vec.y /= static_cast<T>(xm.y);
  vec.z /= static_cast<T>(xm.z);
  vec.w /= static_cast<T>(xm.w);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator/(const DirectX::XMFLOAT2& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x /= static_cast<T>(xm.x);
  vec.y /= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator/(const DirectX::XMFLOAT3& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x /= static_cast<T>(xm.x);
  vec.y /= static_cast<T>(xm.y);
  vec.z /= static_cast<T>(xm.z);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator/(const DirectX::XMFLOAT4& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x /= static_cast<T>(xm.x);
  vec.y /= static_cast<T>(xm.y);
  vec.z /= static_cast<T>(xm.z);
  vec.w /= static_cast<T>(xm.w);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator/(const DirectX::XMFLOAT2A& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x /= static_cast<T>(xm.x);
  vec.y /= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator/(const DirectX::XMFLOAT3A& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x /= static_cast<T>(xm.x);
  vec.y /= static_cast<T>(xm.y);
  vec.z /= static_cast<T>(xm.z);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator/(const DirectX::XMFLOAT4A& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x /= static_cast<T>(xm.x);
  vec.y /= static_cast<T>(xm.y);
  vec.z /= static_cast<T>(xm.z);
  vec.w /= static_cast<T>(xm.w);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator/(const DirectX::XMVECTOR& xm) const
{
  Vec4<T> vec(x, y, z, w);
  vec.x /= static_cast<T>(DirectX::XMVectorGetX(xm));
  vec.y /= static_cast<T>(DirectX::XMVectorGetY(xm));
  vec.z /= static_cast<T>(DirectX::XMVectorGetZ(xm));
  vec.w /= static_cast<T>(DirectX::XMVectorGetW(xm));
  return vec;
}
template <class T>
template <class U>
inline Vec4<T>& Vec4<T>::operator/=(const U& v)
{
  *this = *this / v;
  return *this;
}
template <class T>
template <class U>
inline Vec4<T>& Vec4<T>::operator/=(const Vec2<U>& vec2)
{
  *this = *this / vec2;
  return *this;
}
template <class T>
template <class U>
inline Vec4<T>& Vec4<T>::operator/=(const Vec3<U>& vec3)
{
  *this = *this / vec3;
  return *this;
}
template <class T>
template <class U>
inline Vec4<T>& Vec4<T>::operator/=(const Vec4<U>& vec4)
{
  *this = *this / vec4;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator/=(const DirectX::XMINT2& xm)
{
  *this = *this / xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator/=(const DirectX::XMINT3& xm)
{
  *this = *this / xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator/=(const DirectX::XMINT4& xm)
{
  *this = *this / xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator/=(const DirectX::XMUINT2& xm)
{
  *this = *this / xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator/=(const DirectX::XMUINT3& xm)
{
  *this = *this / xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator/=(const DirectX::XMUINT4& xm)
{
  *this = *this / xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator/=(const DirectX::XMFLOAT2& xm)
{
  *this = *this / xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator/=(const DirectX::XMFLOAT3& xm)
{
  *this = *this / xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator/=(const DirectX::XMFLOAT4& xm)
{
  *this = *this / xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator/=(const DirectX::XMFLOAT2A& xm)
{
  *this = *this / xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator/=(const DirectX::XMFLOAT3A& xm)
{
  *this = *this / xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator/=(const DirectX::XMFLOAT4A& xm)
{
  *this = *this / xm;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator/=(const DirectX::XMVECTOR& xm)
{
  *this = *this / xm;
  return *this;
}

template <class T>
template <class U>
inline bool Vec4<T>::operator==(const U& v) const
{
  return x == static_cast<T>(v) && y == static_cast<T>(v) && z == static_cast<T>(v);
}
template <class T>
template <class U>
inline bool Vec4<T>::operator==(const Vec2<U>& vec2) const
{
  return x == static_cast<T>(vec2.x) && y == static_cast<T>(vec2.y);
}
template <class T>
template <class U>
inline bool Vec4<T>::operator==(const Vec3<U>& vec3) const
{
  return x == static_cast<T>(vec3.x) && y == static_cast<T>(vec3.y) && z == static_cast<T>(vec3.z);
}
template <class T>
template <class U>
inline bool Vec4<T>::operator==(const Vec4<U>& vec4) const
{
  return x == static_cast<T>(vec4.x) && y == static_cast<T>(vec4.y) &&
         z == static_cast<T>(vec4.z) && w == static_cast<T>(vec4.w);
}
template <class T>
inline bool Vec4<T>::operator==(const DirectX::XMINT2& xm) const
{
  return x == static_cast<T>(xm.x) && y == static_cast<T>(xm.y);
}
template <class T>
inline bool Vec4<T>::operator==(const DirectX::XMINT3& xm) const
{
  return x == static_cast<T>(xm.x) && y == static_cast<T>(xm.y) && z == static_cast<T>(xm.z);
}
template <class T>
inline bool Vec4<T>::operator==(const DirectX::XMINT4& xm) const
{
  return x == static_cast<T>(xm.x) && y == static_cast<T>(xm.y) && z == static_cast<T>(xm.z) &&
         w == static_cast<T>(xm.w);
}
template <class T>
inline bool Vec4<T>::operator==(const DirectX::XMUINT2& xm) const
{
  return x == static_cast<T>(xm.x) && y == static_cast<T>(xm.y);
}
template <class T>
inline bool Vec4<T>::operator==(const DirectX::XMUINT3& xm) const
{
  return x == static_cast<T>(xm.x) && y == static_cast<T>(xm.y) && z == static_cast<T>(xm.z);
}
template <class T>
inline bool Vec4<T>::operator==(const DirectX::XMUINT4& xm) const
{
  return x == static_cast<T>(xm.x) && y == static_cast<T>(xm.y) && z == static_cast<T>(xm.z) &&
         w == static_cast<T>(xm.w);
}
template <class T>
inline bool Vec4<T>::operator==(const DirectX::XMFLOAT2& xm) const
{
  return x == static_cast<T>(xm.x) && y == static_cast<T>(xm.y);
}
template <class T>
inline bool Vec4<T>::operator==(const DirectX::XMFLOAT3& xm) const
{
  return x == static_cast<T>(xm.x) && y == static_cast<T>(xm.y) && z == static_cast<T>(xm.z);
}
template <class T>
inline bool Vec4<T>::operator==(const DirectX::XMFLOAT4& xm) const
{
  return x == static_cast<T>(xm.x) && y == static_cast<T>(xm.y) && z == static_cast<T>(xm.z) &&
         w == static_cast<T>(xm.w);
}
template <class T>
inline bool Vec4<T>::operator==(const DirectX::XMFLOAT2A& xm) const
{
  return x == static_cast<T>(xm.x) && y == static_cast<T>(xm.y);
}
template <class T>
inline bool Vec4<T>::operator==(const DirectX::XMFLOAT3A& xm) const
{
  return x == static_cast<T>(xm.x) && y == static_cast<T>(xm.y) && z == static_cast<T>(xm.z);
}
template <class T>
inline bool Vec4<T>::operator==(const DirectX::XMFLOAT4A& xm) const
{
  return x == static_cast<T>(xm.x) && y == static_cast<T>(xm.y) && z == static_cast<T>(xm.z) &&
         w == static_cast<T>(xm.w);
}
template <class T>
inline bool Vec4<T>::operator==(const DirectX::XMVECTOR& xm) const
{
  return x == static_cast<T>(DirectX ::XMVectorGetX(xm)) &&
         y == static_cast<T>(DirectX ::XMVectorGetY(xm)) &&
         z == static_cast<T>(DirectX ::XMVectorGetZ(xm)) &&
         w == static_cast<T>(DirectX ::XMVectorGetW(xm));
}

template <class T>
inline T& Vec4<T>::operator[](unsigned int i)
{
  return data[i];
}
template <class T>
inline T Vec4<T>::operator[](unsigned int i) const
{
  return data[i];
}


#pragma endregion
#pragma region MatrixOperators
template <class T>
inline Vec4<T> Vec4<T>::operator*(const DirectX::XMMATRIX& mat) const
{
  Vec4<T> vec = DirectX::XMVector4Transform(Load(), mat);
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator*(const DirectX::XMFLOAT3X3 mat) const
{
  Vec4<T> vec = DirectX::XMVector4Transform(Load(), DirectX::XMLoadFloat3x3(&mat));
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator*(const DirectX::XMFLOAT4X4 mat) const
{
  Vec4<T> vec = DirectX::XMVector4Transform(Load(), DirectX::XMLoadFloat4x4(&mat));
  return vec;
}
template <class T>
inline Vec4<T> Vec4<T>::operator*(const DirectX::XMFLOAT4X4A mat) const
{
  Vec4<T> vec = DirectX::XMVector4Transform(Load(), DirectX::XMLoadFloat4x4A(&mat));
  return vec;
}
template <class T>
template <class U>
inline Vec4<T> Vec4<T>::operator*(const Mat3x3<U>& mat) const
{
  Vec4<T> vec = DirectX::XMVector4Transform(Load(), mat.Load());
  return vec;
}
template <class T>
template <class U>
inline Vec4<T> Vec4<T>::operator*(const Mat4x4<U>& mat) const
{
  Vec4<T> vec = DirectX::XMVector4Transform(Load(), mat.Load());
  return vec;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator*=(const DirectX::XMMATRIX& mat)
{
  *this = *this * mat;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator*=(const DirectX::XMFLOAT3X3 mat)
{
  *this = *this * mat;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator*=(const DirectX::XMFLOAT4X4 mat)
{
  *this = *this * mat;
  return *this;
}
template <class T>
inline Vec4<T>& Vec4<T>::operator*=(const DirectX::XMFLOAT4X4A mat)
{
  *this = *this * mat;
  return *this;
}
template <class T>
template <class U>
inline Vec4<T>& Vec4<T>::operator*=(const Mat3x3<U>& mat)
{
  *this = *this * mat;
  return *this;
}
template <class T>
template <class U>
inline Vec4<T>& Vec4<T>::operator*=(const Mat4x4<U>& mat)
{
  *this = *this * mat;
  return *this;
}
#pragma endregion
#pragma region Functions
template <class T>
inline DirectX::XMVECTOR Vec4<T>::Load() const
{
  DirectX::XMVECTOR v = DirectX::XMVectorZero();
  v = DirectX::XMVectorSetX(v, static_cast<float>(x));
  v = DirectX::XMVectorSetY(v, static_cast<float>(y));
  v = DirectX::XMVectorSetZ(v, static_cast<float>(z));
  v = DirectX::XMVectorSetW(v, static_cast<float>(w));
  return v;
}
template <class T>
inline void Vec4<T>::Store(const DirectX::XMVECTOR& xm)
{
  x = static_cast<T>(DirectX::XMVectorGetX(xm));
  y = static_cast<T>(DirectX::XMVectorGetY(xm));
  z = static_cast<T>(DirectX::XMVectorGetZ(xm));
  w = static_cast<T>(DirectX::XMVectorGetW(xm));
}

template <class T>
inline T Vec4<T>::Length() const
{
  return static_cast<T>(DirectX::XMVectorGetX(DirectX::XMVector4Length(Load())));
}
template <class T>
inline T Vec4<T>::LengthSq() const
{
  return static_cast<T>(DirectX::XMVectorGetX(DirectX::XMVector4LengthSq(Load())));
}
template <class T>
inline DirectX::XMINT2 Vec4<T>::AsXmInt2() const
{
  DirectX::XMINT2 v {};
  v.x = static_cast<int>(x);
  v.y = static_cast<int>(y);
  return v;
}
template <class T>
inline DirectX::XMINT3 Vec4<T>::AsXmInt3() const
{
  DirectX::XMINT3 v {};
  v.x = static_cast<int>(x);
  v.y = static_cast<int>(y);
  v.z = static_cast<int>(z);
  return v;
}
template <class T>
inline DirectX::XMINT4 Vec4<T>::AsXmInt4() const
{
  DirectX::XMINT4 v {};
  v.x = static_cast<int>(x);
  v.y = static_cast<int>(y);
  v.z = static_cast<int>(z);
  v.w = static_cast<int>(w);
  return v;
}
template <class T>
inline DirectX::XMUINT2 Vec4<T>::AsXmUint2() const
{
  DirectX::XMUINT2 v {};
  v.x = static_cast<unsigned int>(x);
  v.y = static_cast<unsigned int>(y);
  return v;
}
template <class T>
inline DirectX::XMUINT3 Vec4<T>::AsXmUint3() const
{
  DirectX::XMUINT3 v {};
  v.x = static_cast<unsigned int>(x);
  v.y = static_cast<unsigned int>(y);
  v.z = static_cast<unsigned int>(z);
  return v;
}
template <class T>
inline DirectX::XMUINT4 Vec4<T>::AsXmUint4() const
{
  DirectX::XMUINT4 v {};
  v.x = static_cast<unsigned int>(x);
  v.y = static_cast<unsigned int>(y);
  v.z = static_cast<unsigned int>(z);
  v.w = static_cast<unsigned int>(w);
  return v;
}
template <class T>
inline DirectX::XMFLOAT2 Vec4<T>::AsXmFloat2() const
{
  DirectX::XMFLOAT2 v {};
  v.x = static_cast<float>(x);
  v.y = static_cast<float>(y);
  return v;
}
template <class T>
inline DirectX::XMFLOAT3 Vec4<T>::AsXmFloat3() const
{
  DirectX::XMFLOAT3 v {};
  v.x = static_cast<float>(x);
  v.y = static_cast<float>(y);
  v.z = static_cast<float>(z);
  return v;
}
template <class T>
inline DirectX::XMFLOAT4 Vec4<T>::AsXmFloat4() const
{
  DirectX::XMFLOAT4 v {};
  v.x = static_cast<float>(x);
  v.y = static_cast<float>(y);
  v.z = static_cast<float>(z);
  v.w = static_cast<float>(w);
  return v;
}
template <class T>
inline DirectX::XMFLOAT2A Vec4<T>::AsXmAsXmFloat2A() const
{
  DirectX::XMFLOAT2A v {};
  v.x = static_cast<float>(x);
  v.y = static_cast<float>(y);
  return v;
}
template <class T>
inline DirectX::XMFLOAT3A Vec4<T>::AsXmAsXmFloat3A() const
{
  DirectX::XMFLOAT3A v {};
  v.x = static_cast<float>(x);
  v.y = static_cast<float>(y);
  v.z = static_cast<float>(z);
  return v;
}
template <class T>
inline DirectX::XMFLOAT4A Vec4<T>::AsXmAsXmFloat4A() const
{
  DirectX::XMFLOAT4A v {};
  v.x = static_cast<float>(x);
  v.y = static_cast<float>(y);
  v.z = static_cast<float>(z);
  v.w = static_cast<float>(w);
  return v;
}
template <class T>
inline Vec4<T> Vec4<T>::Abs() const
{
  Vec4<T> v = DirectX::XMVectorAbs(Load());
  return v;
}
template <class T>
inline Vec4<T> Vec4<T>::Normalize() const
{
  T       length = Length();
  Vec4<T> v(x / length, y / length, z / length, w / length);
  return v;
}
template <class T>
template <class U>
inline float Vec4<T>::Dot(const Vec4<U>& vec4) const
{
  return DirectX::XMVectorGetX(DirectX::XMVector4Dot(Load(), vec4.Load()));
}
template <class T>
inline float Vec4<T>::Dot(const DirectX::XMINT4& xm) const
{
  return DirectX::XMVectorGetX(DirectX::XMVector4Dot(Load(), DirectX::XMLoadSInt4(&xm)));
}
template <class T>
inline float Vec4<T>::Dot(const DirectX::XMUINT4& xm) const
{
  return DirectX::XMVectorGetX(DirectX::XMVector4Dot(Load(), DirectX::XMLoadUInt4(&xm)));
}
template <class T>
inline float Vec4<T>::Dot(const DirectX::XMFLOAT4& xm) const
{
  return DirectX::XMVectorGetX(DirectX::XMVector4Dot(Load(), DirectX::XMLoadFloat4(&xm)));
}
template <class T>
inline float Vec4<T>::Dot(const DirectX::XMFLOAT4A& xm) const
{
  return DirectX::XMVectorGetX(DirectX::XMVector4Dot(Load(), DirectX::XMLoadFloat4A(&xm)));
}
template <class T>
inline std::string Vec4<T>::ToString() const
{
  std::stringstream ss;
  ss << "[" << x << " " << y << " " << z << " " << w << "]";
  return ss.str();
}

namespace std
{
  template <class T>
  struct hash<Vec4<T>>
  {
    size_t operator()(const Vec4<T>& p) const
    {
      size_t h =
          std::hash<T>()(p.x) ^ std::hash<T>()(p.y) ^ std::hash<T>()(p.z) ^ std::hash<T>()(p.w);
      return h;
    }
  };
}

#pragma endregion