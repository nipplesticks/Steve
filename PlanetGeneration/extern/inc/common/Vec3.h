#pragma once
#include <DirectXMath.h>
#include <cstddef>
#include <sstream>
#include <string>

#pragma region ForwardDeclarations
template <class U>
class Vec2;
template <class U>
class Vec4;
template <class U>
class Mat3x3;
template <class U>
class Mat4x4;
#pragma endregion
template <class T>
class Vec3
{
public:
#pragma region Constructors
  Vec3();
  template <class U>
  Vec3(U v);
  template <class U, class V, class M>
  Vec3(U _x, V _y, M _z);
  template <class U>
  Vec3(const Vec2<U>& vec2);
  template <class U>
  Vec3(const Vec3<U>& vec3);
  template <class U>
  Vec3(const Vec4<U>& vec4);
  Vec3(const DirectX::XMINT2& xm);
  Vec3(const DirectX::XMINT3& xm);
  Vec3(const DirectX::XMINT4& xm);

  Vec3(const DirectX::XMUINT2& xm);
  Vec3(const DirectX::XMUINT3& xm);
  Vec3(const DirectX::XMUINT4& xm);

  Vec3(const DirectX::XMFLOAT2& xm);
  Vec3(const DirectX::XMFLOAT3& xm);
  Vec3(const DirectX::XMFLOAT4& xm);
  Vec3(const DirectX::XMFLOAT2A& xm);
  Vec3(const DirectX::XMFLOAT3A& xm);
  Vec3(const DirectX::XMFLOAT4A& xm);
  Vec3(const DirectX::XMVECTOR& xm);
#pragma endregion
#pragma region VectorOperatiors
  // Asignment Operators
  template <class U>
  Vec3<T>& operator=(const U& v);
  template <class U>
  Vec3<T>& operator=(const Vec2<U>& vec2);
  template <class U>
  Vec3<T>& operator=(const Vec3<U>& vec3);
  template <class U>
  Vec3<T>& operator=(const Vec4<U>& vec4);
  Vec3<T>& operator=(const DirectX::XMINT2& xm);
  Vec3<T>& operator=(const DirectX::XMINT3& xm);
  Vec3<T>& operator=(const DirectX::XMINT4& xm);
  Vec3<T>& operator=(const DirectX::XMUINT2& xm);
  Vec3<T>& operator=(const DirectX::XMUINT3& xm);
  Vec3<T>& operator=(const DirectX::XMUINT4& xm);
  Vec3<T>& operator=(const DirectX::XMFLOAT2& xm);
  Vec3<T>& operator=(const DirectX::XMFLOAT3& xm);
  Vec3<T>& operator=(const DirectX::XMFLOAT4& xm);
  Vec3<T>& operator=(const DirectX::XMFLOAT2A& xm);
  Vec3<T>& operator=(const DirectX::XMFLOAT3A& xm);
  Vec3<T>& operator=(const DirectX::XMFLOAT4A& xm);
  Vec3<T>& operator=(const DirectX::XMVECTOR& xm);

  // Addition operators
  template <class U>
  Vec3<T> operator+(const U& v) const;
  template <class U>
  Vec3<T> operator+(const Vec2<U>& vec2) const;
  template <class U>
  Vec3<T> operator+(const Vec3<U>& vec3) const;
  template <class U>
  Vec3<T> operator+(const Vec4<U>& vec4) const;
  Vec3<T> operator+(const DirectX::XMINT2& xm) const;
  Vec3<T> operator+(const DirectX::XMINT3& xm) const;
  Vec3<T> operator+(const DirectX::XMINT4& xm) const;
  Vec3<T> operator+(const DirectX::XMUINT2& xm) const;
  Vec3<T> operator+(const DirectX::XMUINT3& xm) const;
  Vec3<T> operator+(const DirectX::XMUINT4& xm) const;
  Vec3<T> operator+(const DirectX::XMFLOAT2& xm) const;
  Vec3<T> operator+(const DirectX::XMFLOAT3& xm) const;
  Vec3<T> operator+(const DirectX::XMFLOAT4& xm) const;
  Vec3<T> operator+(const DirectX::XMFLOAT2A& xm) const;
  Vec3<T> operator+(const DirectX::XMFLOAT3A& xm) const;
  Vec3<T> operator+(const DirectX::XMFLOAT4A& xm) const;
  Vec3<T> operator+(const DirectX::XMVECTOR& xm) const;
  template <class U>
  Vec3<T>& operator+=(const U& v);
  template <class U>
  Vec3<T>& operator+=(const Vec2<U>& vec2);
  template <class U>
  Vec3<T>& operator+=(const Vec3<U>& vec3);
  template <class U>
  Vec3<T>& operator+=(const Vec4<U>& vec4);
  Vec3<T>& operator+=(const DirectX::XMINT2& xm);
  Vec3<T>& operator+=(const DirectX::XMINT3& xm);
  Vec3<T>& operator+=(const DirectX::XMINT4& xm);
  Vec3<T>& operator+=(const DirectX::XMUINT2& xm);
  Vec3<T>& operator+=(const DirectX::XMUINT3& xm);
  Vec3<T>& operator+=(const DirectX::XMUINT4& xm);
  Vec3<T>& operator+=(const DirectX::XMFLOAT2& xm);
  Vec3<T>& operator+=(const DirectX::XMFLOAT3& xm);
  Vec3<T>& operator+=(const DirectX::XMFLOAT4& xm);
  Vec3<T>& operator+=(const DirectX::XMFLOAT2A& xm);
  Vec3<T>& operator+=(const DirectX::XMFLOAT3A& xm);
  Vec3<T>& operator+=(const DirectX::XMFLOAT4A& xm);
  Vec3<T>& operator+=(const DirectX::XMVECTOR& xm);

  // Subtraction operators
  template <class U>
  Vec3<T> operator-(const U& v) const;
  template <class U>
  Vec3<T> operator-(const Vec2<U>& vec2) const;
  template <class U>
  Vec3<T> operator-(const Vec3<U>& vec3) const;
  template <class U>
  Vec3<T> operator-(const Vec4<U>& vec4) const;
  Vec3<T> operator-(const DirectX::XMINT2& xm) const;
  Vec3<T> operator-(const DirectX::XMINT3& xm) const;
  Vec3<T> operator-(const DirectX::XMINT4& xm) const;
  Vec3<T> operator-(const DirectX::XMUINT2& xm) const;
  Vec3<T> operator-(const DirectX::XMUINT3& xm) const;
  Vec3<T> operator-(const DirectX::XMUINT4& xm) const;
  Vec3<T> operator-(const DirectX::XMFLOAT2& xm) const;
  Vec3<T> operator-(const DirectX::XMFLOAT3& xm) const;
  Vec3<T> operator-(const DirectX::XMFLOAT4& xm) const;
  Vec3<T> operator-(const DirectX::XMFLOAT2A& xm) const;
  Vec3<T> operator-(const DirectX::XMFLOAT3A& xm) const;
  Vec3<T> operator-(const DirectX::XMFLOAT4A& xm) const;
  Vec3<T> operator-(const DirectX::XMVECTOR& xm) const;
  template <class U>
  Vec3<T>& operator-=(const U& v);
  template <class U>
  Vec3<T>& operator-=(const Vec2<U>& vec2);
  template <class U>
  Vec3<T>& operator-=(const Vec3<U>& vec3);
  template <class U>
  Vec3<T>& operator-=(const Vec4<U>& vec4);
  Vec3<T>& operator-=(const DirectX::XMINT2& xm);
  Vec3<T>& operator-=(const DirectX::XMINT3& xm);
  Vec3<T>& operator-=(const DirectX::XMINT4& xm);
  Vec3<T>& operator-=(const DirectX::XMUINT2& xm);
  Vec3<T>& operator-=(const DirectX::XMUINT3& xm);
  Vec3<T>& operator-=(const DirectX::XMUINT4& xm);
  Vec3<T>& operator-=(const DirectX::XMFLOAT2& xm);
  Vec3<T>& operator-=(const DirectX::XMFLOAT3& xm);
  Vec3<T>& operator-=(const DirectX::XMFLOAT4& xm);
  Vec3<T>& operator-=(const DirectX::XMFLOAT2A& xm);
  Vec3<T>& operator-=(const DirectX::XMFLOAT3A& xm);
  Vec3<T>& operator-=(const DirectX::XMFLOAT4A& xm);
  Vec3<T>& operator-=(const DirectX::XMVECTOR& xm);

  // Multiplication operators
  template <class U>
  Vec3<T> operator*(const U& v) const;
  template <class U>
  Vec3<T> operator*(const Vec2<U>& vec2) const;
  template <class U>
  Vec3<T> operator*(const Vec3<U>& vec3) const;
  template <class U>
  Vec3<T> operator*(const Vec4<U>& vec4) const;
  Vec3<T> operator*(const DirectX::XMINT2& xm) const;
  Vec3<T> operator*(const DirectX::XMINT3& xm) const;
  Vec3<T> operator*(const DirectX::XMINT4& xm) const;
  Vec3<T> operator*(const DirectX::XMUINT2& xm) const;
  Vec3<T> operator*(const DirectX::XMUINT3& xm) const;
  Vec3<T> operator*(const DirectX::XMUINT4& xm) const;
  Vec3<T> operator*(const DirectX::XMFLOAT2& xm) const;
  Vec3<T> operator*(const DirectX::XMFLOAT3& xm) const;
  Vec3<T> operator*(const DirectX::XMFLOAT4& xm) const;
  Vec3<T> operator*(const DirectX::XMFLOAT2A& xm) const;
  Vec3<T> operator*(const DirectX::XMFLOAT3A& xm) const;
  Vec3<T> operator*(const DirectX::XMFLOAT4A& xm) const;
  Vec3<T> operator*(const DirectX::XMVECTOR& xm) const;
  template <class U>
  Vec3<T>& operator*=(const U& v);
  template <class U>
  Vec3<T>& operator*=(const Vec2<U>& vec2);
  template <class U>
  Vec3<T>& operator*=(const Vec3<U>& vec3);
  template <class U>
  Vec3<T>& operator*=(const Vec4<U>& vec4);
  Vec3<T>& operator*=(const DirectX::XMINT2& xm);
  Vec3<T>& operator*=(const DirectX::XMINT3& xm);
  Vec3<T>& operator*=(const DirectX::XMINT4& xm);
  Vec3<T>& operator*=(const DirectX::XMUINT2& xm);
  Vec3<T>& operator*=(const DirectX::XMUINT3& xm);
  Vec3<T>& operator*=(const DirectX::XMUINT4& xm);
  Vec3<T>& operator*=(const DirectX::XMFLOAT2& xm);
  Vec3<T>& operator*=(const DirectX::XMFLOAT3& xm);
  Vec3<T>& operator*=(const DirectX::XMFLOAT4& xm);
  Vec3<T>& operator*=(const DirectX::XMFLOAT2A& xm);
  Vec3<T>& operator*=(const DirectX::XMFLOAT3A& xm);
  Vec3<T>& operator*=(const DirectX::XMFLOAT4A& xm);
  Vec3<T>& operator*=(const DirectX::XMVECTOR& xm);

  // Divition operators
  template <class U>
  Vec3<T> operator/(const U& v) const;
  template <class U>
  Vec3<T> operator/(const Vec2<U>& vec2) const;
  template <class U>
  Vec3<T> operator/(const Vec3<U>& vec3) const;
  template <class U>
  Vec3<T> operator/(const Vec4<U>& vec4) const;
  Vec3<T> operator/(const DirectX::XMINT2& xm) const;
  Vec3<T> operator/(const DirectX::XMINT3& xm) const;
  Vec3<T> operator/(const DirectX::XMINT4& xm) const;
  Vec3<T> operator/(const DirectX::XMUINT2& xm) const;
  Vec3<T> operator/(const DirectX::XMUINT3& xm) const;
  Vec3<T> operator/(const DirectX::XMUINT4& xm) const;
  Vec3<T> operator/(const DirectX::XMFLOAT2& xm) const;
  Vec3<T> operator/(const DirectX::XMFLOAT3& xm) const;
  Vec3<T> operator/(const DirectX::XMFLOAT4& xm) const;
  Vec3<T> operator/(const DirectX::XMFLOAT2A& xm) const;
  Vec3<T> operator/(const DirectX::XMFLOAT3A& xm) const;
  Vec3<T> operator/(const DirectX::XMFLOAT4A& xm) const;
  Vec3<T> operator/(const DirectX::XMVECTOR& xm) const;
  template <class U>
  Vec3<T>& operator/=(const U& v);
  template <class U>
  Vec3<T>& operator/=(const Vec2<U>& vec2);
  template <class U>
  Vec3<T>& operator/=(const Vec3<U>& vec3);
  template <class U>
  Vec3<T>& operator/=(const Vec4<U>& vec4);
  Vec3<T>& operator/=(const DirectX::XMINT2& xm);
  Vec3<T>& operator/=(const DirectX::XMINT3& xm);
  Vec3<T>& operator/=(const DirectX::XMINT4& xm);
  Vec3<T>& operator/=(const DirectX::XMUINT2& xm);
  Vec3<T>& operator/=(const DirectX::XMUINT3& xm);
  Vec3<T>& operator/=(const DirectX::XMUINT4& xm);
  Vec3<T>& operator/=(const DirectX::XMFLOAT2& xm);
  Vec3<T>& operator/=(const DirectX::XMFLOAT3& xm);
  Vec3<T>& operator/=(const DirectX::XMFLOAT4& xm);
  Vec3<T>& operator/=(const DirectX::XMFLOAT2A& xm);
  Vec3<T>& operator/=(const DirectX::XMFLOAT3A& xm);
  Vec3<T>& operator/=(const DirectX::XMFLOAT4A& xm);
  Vec3<T>& operator/=(const DirectX::XMVECTOR& xm);

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
#pragma region MatrixOperators
  Vec3<T> operator*(const DirectX::XMMATRIX& mat) const;
  Vec3<T> operator*(const DirectX::XMFLOAT3X3 mat) const;
  Vec3<T> operator*(const DirectX::XMFLOAT4X4 mat) const;
  Vec3<T> operator*(const DirectX::XMFLOAT4X4A mat) const;
  template <class U>
  Vec3<T> operator*(const Mat3x3<U>& mat) const;
  template <class U>
  Vec3<T> operator*(const Mat4x4<U>& mat) const;

  Vec3<T>& operator*=(const DirectX::XMMATRIX& mat);
  Vec3<T>& operator*=(const DirectX::XMFLOAT3X3 mat);
  Vec3<T>& operator*=(const DirectX::XMFLOAT4X4 mat);
  Vec3<T>& operator*=(const DirectX::XMFLOAT4X4A mat);
  template <class U>
  Vec3<T>& operator*=(const Mat3x3<U>& mat);
  template <class U>
  Vec3<T>& operator*=(const Mat4x4<U>& mat);

#pragma endregion
#pragma region Functions
  template <class U>
  DirectX::XMVECTOR  Load(U w) const;
  DirectX::XMVECTOR  Load() const;
  void               Store(const DirectX::XMVECTOR& xm);
  T                  Length() const;
  T                  LengthSq() const;
  DirectX::XMINT2    AsXmInt2() const;
  DirectX::XMINT3    AsXmInt3() const;
  DirectX::XMINT4    AsXmInt4(int w = 0) const;
  DirectX::XMUINT2   AsXmUint2() const;
  DirectX::XMUINT3   AsXmUint3() const;
  DirectX::XMUINT4   AsXmUint4(unsigned int w = 0) const;
  DirectX::XMFLOAT2  AsXmFloat2() const;
  DirectX::XMFLOAT3  AsXmFloat3() const;
  DirectX::XMFLOAT4  AsXmFloat4(float w = 0.0f) const;
  DirectX::XMFLOAT2A AsXmAsXmFloat2A() const;
  DirectX::XMFLOAT3A AsXmAsXmFloat3A() const;
  DirectX::XMFLOAT4A AsXmAsXmFloat4A(float w = 0.0f) const;
  template <class U>
  Vec3<T> Cross(const Vec3<U>& vec3) const;
  Vec3<T> Cross(const DirectX::XMFLOAT3& xm) const;
  Vec3<T> Cross(const DirectX::XMFLOAT3A& xm) const;
  Vec3<T> Cross(const DirectX::XMVECTOR& xm) const;
  Vec3<T> Abs() const;
  Vec3<T> Normalize() const;
  template <class U>
  Mat3x3<T> GetRotationFrom(const Vec3<U>& vec3);
  template <class U>
  float Dot(const Vec3<U>& Vec3) const;
  float Dot(const DirectX::XMINT3& xm) const;
  float Dot(const DirectX::XMUINT3& xm) const;
  float Dot(const DirectX::XMFLOAT3& xm) const;
  float Dot(const DirectX::XMFLOAT3A& xm) const;
  template <class U>
  float       Angle(const Vec3<U>& Vec3) const;
  float       Angle(const DirectX::XMINT3& xm) const;
  float       Angle(const DirectX::XMUINT3& xm) const;
  float       Angle(const DirectX::XMFLOAT3& xm) const;
  float       Angle(const DirectX::XMFLOAT3A& xm) const;
  float       Angle(float dot, float lenSq1, float lenSq2) const;
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
    };
    struct
    {
      T r;
      T g;
      T b;
    };
    T data[3];
  };
#pragma endregion
};
#include "Mat3x3.h"
#include "Mat4x4.h"
#include "Vec2.h"
#include "Vec4.h"
#pragma region Constructors
template <class T>
inline Vec3<T>::Vec3()
{
  x = static_cast<T>(0);
  y = static_cast<T>(0);
  z = static_cast<T>(0);
}

template <class T>
template <class U>
inline Vec3<T>::Vec3(U v)
{
  x = static_cast<T>(v);
  y = static_cast<T>(v);
  z = static_cast<T>(v);
}
template <class T>
template <class U, class V, class M>
inline Vec3<T>::Vec3(U _x, V _y, M _z)
{
  x = static_cast<T>(_x);
  y = static_cast<T>(_y);
  z = static_cast<T>(_z);
}

template <class T>
template <class U>
inline Vec3<T>::Vec3(const Vec2<U>& vec2)
{
  x = static_cast<T>(vec2.x);
  y = static_cast<T>(vec2.y);
  z = static_cast<T>(0);
}

template <class T>
template <class U>
inline Vec3<T>::Vec3(const Vec3<U>& vec3)
{
  x = static_cast<T>(vec3.x);
  y = static_cast<T>(vec3.y);
  z = static_cast<T>(vec3.z);
}

template <class T>
template <class U>
inline Vec3<T>::Vec3(const Vec4<U>& vec4)
{
  x = static_cast<T>(vec4.x);
  y = static_cast<T>(vec4.y);
  z = static_cast<T>(vec4.z);
}

template <class T>
inline Vec3<T>::Vec3(const DirectX::XMINT2& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(0);
}

template <class T>
inline Vec3<T>::Vec3(const DirectX::XMINT3& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(xm.z);
}

template <class T>
inline Vec3<T>::Vec3(const DirectX::XMINT4& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(xm.z);
}

template <class T>
inline Vec3<T>::Vec3(const DirectX::XMUINT2& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(0);
}

template <class T>
inline Vec3<T>::Vec3(const DirectX::XMUINT3& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(xm.z);
}

template <class T>
inline Vec3<T>::Vec3(const DirectX::XMUINT4& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(xm.z);
}

template <class T>
inline Vec3<T>::Vec3(const DirectX::XMFLOAT2& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(0);
}

template <class T>
inline Vec3<T>::Vec3(const DirectX::XMFLOAT3& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(xm.z);
}

template <class T>
inline Vec3<T>::Vec3(const DirectX::XMFLOAT4& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(xm.z);
}

template <class T>
inline Vec3<T>::Vec3(const DirectX::XMFLOAT2A& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(0);
}

template <class T>
inline Vec3<T>::Vec3(const DirectX::XMFLOAT3A& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(xm.z);
}

template <class T>
inline Vec3<T>::Vec3(const DirectX::XMFLOAT4A& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(xm.z);
}

template <class T>
inline Vec3<T>::Vec3(const DirectX::XMVECTOR& xm)
{
  x = static_cast<T>(DirectX::XMVectorGetX(xm));
  y = static_cast<T>(DirectX::XMVectorGetY(xm));
  z = static_cast<T>(DirectX::XMVectorGetZ(xm));
}
#pragma endregion
#pragma region VectorOperatiors
template <class T>
template <class U>
inline Vec3<T>& Vec3<T>::operator=(const U& v)
{
  x = static_cast<T>(v);
  y = static_cast<T>(v);
  z = static_cast<T>(v);
  return *this;
}
template <class T>
template <class U>
inline Vec3<T>& Vec3<T>::operator=(const Vec2<U>& vec2)
{
  x = static_cast<T>(vec2.x);
  y = static_cast<T>(vec2.y);
  z = static_cast<T>(0);
  return *this;
}
template <class T>
template <class U>
inline Vec3<T>& Vec3<T>::operator=(const Vec3<U>& vec3)
{
  x = static_cast<T>(vec3.x);
  y = static_cast<T>(vec3.y);
  z = static_cast<T>(vec3.z);
  return *this;
}
template <class T>
template <class U>
inline Vec3<T>& Vec3<T>::operator=(const Vec4<U>& vec4)
{
  x = static_cast<T>(vec4.x);
  y = static_cast<T>(vec4.y);
  z = static_cast<T>(vec4.z);
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator=(const DirectX::XMINT2& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(0);
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator=(const DirectX::XMINT3& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(xm.z);
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator=(const DirectX::XMINT4& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(xm.z);
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator=(const DirectX::XMUINT2& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(0);
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator=(const DirectX::XMUINT3& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(xm.z);
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator=(const DirectX::XMUINT4& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(xm.z);
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator=(const DirectX::XMFLOAT2& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(0);
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator=(const DirectX::XMFLOAT3& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(xm.z);
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator=(const DirectX::XMFLOAT4& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(xm.z);
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator=(const DirectX::XMFLOAT2A& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(0);
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator=(const DirectX::XMFLOAT3A& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(xm.z);
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator=(const DirectX::XMFLOAT4A& xm)
{
  x = static_cast<T>(xm.x);
  y = static_cast<T>(xm.y);
  z = static_cast<T>(xm.z);
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator=(const DirectX::XMVECTOR& xm)
{
  x = static_cast<T>(DirectX::XMVectorGetX(xm));
  y = static_cast<T>(DirectX::XMVectorGetY(xm));
  z = static_cast<T>(DirectX::XMVectorGetZ(xm));
  return *this;
}
template <class T>
template <class U>
inline Vec3<T> Vec3<T>::operator+(const U& v) const
{
  Vec3<T> vec(x, y, z);
  vec.x += static_cast<T>(v);
  vec.y += static_cast<T>(v);
  vec.z += static_cast<T>(v);
  return vec;
}
template <class T>
template <class U>
inline Vec3<T> Vec3<T>::operator+(const Vec2<U>& vec2) const
{
  Vec3<T> vec(x, y, z);
  vec.x += static_cast<T>(vec2.x);
  vec.y += static_cast<T>(vec2.y);
  vec.z += static_cast<T>(0);
  return vec;
}
template <class T>
template <class U>
inline Vec3<T> Vec3<T>::operator+(const Vec3<U>& vec3) const
{
  Vec3<T> vec(x, y, z);
  vec.x += static_cast<T>(vec3.x);
  vec.y += static_cast<T>(vec3.y);
  vec.z += static_cast<T>(vec3.z);
  return vec;
}
template <class T>
template <class U>
inline Vec3<T> Vec3<T>::operator+(const Vec4<U>& vec4) const
{
  Vec3<T> vec(x, y, z);
  vec.x += static_cast<T>(vec4.x);
  vec.y += static_cast<T>(vec4.y);
  vec.z += static_cast<T>(vec4.z);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator+(const DirectX::XMINT2& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x += static_cast<T>(xm.x);
  vec.y += static_cast<T>(xm.y);
  vec.z += static_cast<T>(0);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator+(const DirectX::XMINT3& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x += static_cast<T>(xm.x);
  vec.y += static_cast<T>(xm.y);
  vec.z += static_cast<T>(xm.z);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator+(const DirectX::XMINT4& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x += static_cast<T>(xm.x);
  vec.y += static_cast<T>(xm.y);
  vec.z += static_cast<T>(xm.z);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator+(const DirectX::XMUINT2& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x += static_cast<T>(xm.x);
  vec.y += static_cast<T>(xm.y);
  vec.z += static_cast<T>(0);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator+(const DirectX::XMUINT3& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x += static_cast<T>(xm.x);
  vec.y += static_cast<T>(xm.y);
  vec.z += static_cast<T>(xm.z);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator+(const DirectX::XMUINT4& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x += static_cast<T>(xm.x);
  vec.y += static_cast<T>(xm.y);
  vec.z += static_cast<T>(xm.z);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator+(const DirectX::XMFLOAT2& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x += static_cast<T>(xm.x);
  vec.y += static_cast<T>(xm.y);
  vec.z += static_cast<T>(0);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator+(const DirectX::XMFLOAT3& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x += static_cast<T>(xm.x);
  vec.y += static_cast<T>(xm.y);
  vec.z += static_cast<T>(xm.z);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator+(const DirectX::XMFLOAT4& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x += static_cast<T>(xm.x);
  vec.y += static_cast<T>(xm.y);
  vec.z += static_cast<T>(xm.z);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator+(const DirectX::XMFLOAT2A& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x += static_cast<T>(xm.x);
  vec.y += static_cast<T>(xm.y);
  vec.z += static_cast<T>(0);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator+(const DirectX::XMFLOAT3A& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x += static_cast<T>(xm.x);
  vec.y += static_cast<T>(xm.y);
  vec.z += static_cast<T>(xm.z);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator+(const DirectX::XMFLOAT4A& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x += static_cast<T>(xm.x);
  vec.y += static_cast<T>(xm.y);
  vec.z += static_cast<T>(xm.z);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator+(const DirectX::XMVECTOR& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x += static_cast<T>(DirectX::XMVectorGetX(xm));
  vec.y += static_cast<T>(DirectX::XMVectorGetY(xm));
  vec.z += static_cast<T>(DirectX::XMVectorGetZ(xm));
  return vec;
}
template <class T>
template <class U>
inline Vec3<T>& Vec3<T>::operator+=(const U& v)
{
  *this = *this + v;
  return *this;
}
template <class T>
template <class U>
inline Vec3<T>& Vec3<T>::operator+=(const Vec2<U>& vec2)
{
  *this = *this + vec2;
  return *this;
}
template <class T>
template <class U>
inline Vec3<T>& Vec3<T>::operator+=(const Vec3<U>& vec3)
{
  *this = *this + vec3;
  return *this;
}
template <class T>
template <class U>
inline Vec3<T>& Vec3<T>::operator+=(const Vec4<U>& vec4)
{
  *this = *this + vec4;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator+=(const DirectX::XMINT2& xm)
{
  *this = *this + xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator+=(const DirectX::XMINT3& xm)
{
  *this = *this + xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator+=(const DirectX::XMINT4& xm)
{
  *this = *this + xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator+=(const DirectX::XMUINT2& xm)
{
  *this = *this + xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator+=(const DirectX::XMUINT3& xm)
{
  *this = *this + xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator+=(const DirectX::XMUINT4& xm)
{
  *this = *this + xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator+=(const DirectX::XMFLOAT2& xm)
{
  *this = *this + xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator+=(const DirectX::XMFLOAT3& xm)
{
  *this = *this + xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator+=(const DirectX::XMFLOAT4& xm)
{
  *this = *this + xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator+=(const DirectX::XMFLOAT2A& xm)
{
  *this = *this + xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator+=(const DirectX::XMFLOAT3A& xm)
{
  *this = *this + xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator+=(const DirectX::XMFLOAT4A& xm)
{
  *this = *this + xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator+=(const DirectX::XMVECTOR& xm)
{
  *this = *this + xm;
  return *this;
}
template <class T>
template <class U>
inline Vec3<T> Vec3<T>::operator-(const U& v) const
{
  Vec3<T> vec(x, y, z);
  vec.x -= static_cast<T>(v);
  vec.y -= static_cast<T>(v);
  vec.z -= static_cast<T>(v);
  return vec;
}
template <class T>
template <class U>
inline Vec3<T> Vec3<T>::operator-(const Vec2<U>& vec2) const
{
  Vec3<T> vec(x, y, z);
  vec.x -= static_cast<T>(vec2.x);
  vec.y -= static_cast<T>(vec2.y);
  vec.z -= static_cast<T>(0);
  return vec;
}
template <class T>
template <class U>
inline Vec3<T> Vec3<T>::operator-(const Vec3<U>& vec3) const
{
  Vec3<T> vec(x, y, z);
  vec.x -= static_cast<T>(vec3.x);
  vec.y -= static_cast<T>(vec3.y);
  vec.z -= static_cast<T>(vec3.z);
  return vec;
}
template <class T>
template <class U>
inline Vec3<T> Vec3<T>::operator-(const Vec4<U>& vec4) const
{
  Vec3<T> vec(x, y, z);
  vec.x -= static_cast<T>(vec4.x);
  vec.y -= static_cast<T>(vec4.y);
  vec.z -= static_cast<T>(vec4.z);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator-(const DirectX::XMINT2& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x -= static_cast<T>(xm.x);
  vec.y -= static_cast<T>(xm.y);
  vec.z -= static_cast<T>(0);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator-(const DirectX::XMINT3& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x -= static_cast<T>(xm.x);
  vec.y -= static_cast<T>(xm.y);
  vec.z -= static_cast<T>(xm.z);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator-(const DirectX::XMINT4& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x -= static_cast<T>(xm.x);
  vec.y -= static_cast<T>(xm.y);
  vec.z -= static_cast<T>(xm.z);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator-(const DirectX::XMUINT2& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x -= static_cast<T>(xm.x);
  vec.y -= static_cast<T>(xm.y);
  vec.z -= static_cast<T>(0);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator-(const DirectX::XMUINT3& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x -= static_cast<T>(xm.x);
  vec.y -= static_cast<T>(xm.y);
  vec.z -= static_cast<T>(xm.z);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator-(const DirectX::XMUINT4& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x -= static_cast<T>(xm.x);
  vec.y -= static_cast<T>(xm.y);
  vec.z -= static_cast<T>(xm.z);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator-(const DirectX::XMFLOAT2& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x -= static_cast<T>(xm.x);
  vec.y -= static_cast<T>(xm.y);
  vec.z -= static_cast<T>(0);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator-(const DirectX::XMFLOAT3& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x -= static_cast<T>(xm.x);
  vec.y -= static_cast<T>(xm.y);
  vec.z -= static_cast<T>(xm.z);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator-(const DirectX::XMFLOAT4& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x -= static_cast<T>(xm.x);
  vec.y -= static_cast<T>(xm.y);
  vec.z -= static_cast<T>(xm.z);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator-(const DirectX::XMFLOAT2A& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x -= static_cast<T>(xm.x);
  vec.y -= static_cast<T>(xm.y);
  vec.z -= static_cast<T>(0);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator-(const DirectX::XMFLOAT3A& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x -= static_cast<T>(xm.x);
  vec.y -= static_cast<T>(xm.y);
  vec.z -= static_cast<T>(xm.z);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator-(const DirectX::XMFLOAT4A& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x -= static_cast<T>(xm.x);
  vec.y -= static_cast<T>(xm.y);
  vec.z -= static_cast<T>(xm.z);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator-(const DirectX::XMVECTOR& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x -= static_cast<T>(DirectX::XMVectorGetX(xm));
  vec.y -= static_cast<T>(DirectX::XMVectorGetY(xm));
  vec.z -= static_cast<T>(DirectX::XMVectorGetZ(xm));
  return vec;
}
template <class T>
template <class U>
inline Vec3<T>& Vec3<T>::operator-=(const U& v)
{
  *this = *this - v;
  return *this;
}
template <class T>
template <class U>
inline Vec3<T>& Vec3<T>::operator-=(const Vec2<U>& vec2)
{
  *this = *this - vec2;
  return *this;
}
template <class T>
template <class U>
inline Vec3<T>& Vec3<T>::operator-=(const Vec3<U>& vec3)
{
  *this = *this - vec3;
  return *this;
}
template <class T>
template <class U>
inline Vec3<T>& Vec3<T>::operator-=(const Vec4<U>& vec4)
{
  *this = *this - vec4;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator-=(const DirectX::XMINT2& xm)
{
  *this = *this - xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator-=(const DirectX::XMINT3& xm)
{
  *this = *this - xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator-=(const DirectX::XMINT4& xm)
{
  *this = *this - xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator-=(const DirectX::XMUINT2& xm)
{
  *this = *this - xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator-=(const DirectX::XMUINT3& xm)
{
  *this = *this - xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator-=(const DirectX::XMUINT4& xm)
{
  *this = *this - xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator-=(const DirectX::XMFLOAT2& xm)
{
  *this = *this - xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator-=(const DirectX::XMFLOAT3& xm)
{
  *this = *this - xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator-=(const DirectX::XMFLOAT4& xm)
{
  *this = *this - xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator-=(const DirectX::XMFLOAT2A& xm)
{
  *this = *this - xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator-=(const DirectX::XMFLOAT3A& xm)
{
  *this = *this - xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator-=(const DirectX::XMFLOAT4A& xm)
{
  *this = *this - xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator-=(const DirectX::XMVECTOR& xm)
{
  *this = *this - xm;
  return *this;
}
template <class T>
template <class U>
inline Vec3<T> Vec3<T>::operator*(const U& v) const
{
  Vec3<T> vec(x, y, z);
  vec.x *= static_cast<T>(v);
  vec.y *= static_cast<T>(v);
  vec.z *= static_cast<T>(v);
  return vec;
}
template <class T>
template <class U>
inline Vec3<T> Vec3<T>::operator*(const Vec2<U>& vec2) const
{
  Vec3<T> vec(x, y, z);
  vec.x *= static_cast<T>(vec2.x);
  vec.y *= static_cast<T>(vec2.y);
  vec.z *= static_cast<T>(0);
  return vec;
}
template <class T>
template <class U>
inline Vec3<T> Vec3<T>::operator*(const Vec3<U>& vec3) const
{
  Vec3<T> vec(x, y, z);
  vec.x *= static_cast<T>(vec3.x);
  vec.y *= static_cast<T>(vec3.y);
  vec.z *= static_cast<T>(vec3.z);
  return vec;
}
template <class T>
template <class U>
inline Vec3<T> Vec3<T>::operator*(const Vec4<U>& vec4) const
{
  Vec3<T> vec(x, y, z);
  vec.x *= static_cast<T>(vec4.x);
  vec.y *= static_cast<T>(vec4.y);
  vec.z *= static_cast<T>(vec4.z);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator*(const DirectX::XMINT2& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x *= static_cast<T>(xm.x);
  vec.y *= static_cast<T>(xm.y);
  vec.z *= static_cast<T>(0);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator*(const DirectX::XMINT3& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x *= static_cast<T>(xm.x);
  vec.y *= static_cast<T>(xm.y);
  vec.z *= static_cast<T>(xm.z);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator*(const DirectX::XMINT4& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x *= static_cast<T>(xm.x);
  vec.y *= static_cast<T>(xm.y);
  vec.z *= static_cast<T>(xm.z);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator*(const DirectX::XMUINT2& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x *= static_cast<T>(xm.x);
  vec.y *= static_cast<T>(xm.y);
  vec.z *= static_cast<T>(0);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator*(const DirectX::XMUINT3& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x *= static_cast<T>(xm.x);
  vec.y *= static_cast<T>(xm.y);
  vec.z *= static_cast<T>(xm.z);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator*(const DirectX::XMUINT4& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x *= static_cast<T>(xm.x);
  vec.y *= static_cast<T>(xm.y);
  vec.z *= static_cast<T>(xm.z);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator*(const DirectX::XMFLOAT2& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x *= static_cast<T>(xm.x);
  vec.y *= static_cast<T>(xm.y);
  vec.z *= static_cast<T>(0);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator*(const DirectX::XMFLOAT3& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x *= static_cast<T>(xm.x);
  vec.y *= static_cast<T>(xm.y);
  vec.z *= static_cast<T>(xm.z);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator*(const DirectX::XMFLOAT4& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x *= static_cast<T>(xm.x);
  vec.y *= static_cast<T>(xm.y);
  vec.z *= static_cast<T>(xm.z);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator*(const DirectX::XMFLOAT2A& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x *= static_cast<T>(xm.x);
  vec.y *= static_cast<T>(xm.y);
  vec.z *= static_cast<T>(0);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator*(const DirectX::XMFLOAT3A& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x *= static_cast<T>(xm.x);
  vec.y *= static_cast<T>(xm.y);
  vec.z *= static_cast<T>(xm.z);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator*(const DirectX::XMFLOAT4A& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x *= static_cast<T>(xm.x);
  vec.y *= static_cast<T>(xm.y);
  vec.z *= static_cast<T>(xm.z);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator*(const DirectX::XMVECTOR& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x *= static_cast<T>(DirectX::XMVectorGetX(xm));
  vec.y *= static_cast<T>(DirectX::XMVectorGetY(xm));
  vec.z *= static_cast<T>(DirectX::XMVectorGetZ(xm));
  return vec;
}
template <class T>
template <class U>
inline Vec3<T>& Vec3<T>::operator*=(const U& v)
{
  *this = *this * v;
  return *this;
}
template <class T>
template <class U>
inline Vec3<T>& Vec3<T>::operator*=(const Vec2<U>& vec2)
{
  *this = *this * vec2;
  return *this;
}
template <class T>
template <class U>
inline Vec3<T>& Vec3<T>::operator*=(const Vec3<U>& vec3)
{
  *this = *this * vec3;
  return *this;
}
template <class T>
template <class U>
inline Vec3<T>& Vec3<T>::operator*=(const Vec4<U>& vec4)
{
  *this = *this * vec4;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator*=(const DirectX::XMINT2& xm)
{
  *this = *this * xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator*=(const DirectX::XMINT3& xm)
{
  *this = *this * xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator*=(const DirectX::XMINT4& xm)
{
  *this = *this * xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator*=(const DirectX::XMUINT2& xm)
{
  *this = *this * xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator*=(const DirectX::XMUINT3& xm)
{
  *this = *this * xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator*=(const DirectX::XMUINT4& xm)
{
  *this = *this * xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator*=(const DirectX::XMFLOAT2& xm)
{
  *this = *this * xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator*=(const DirectX::XMFLOAT3& xm)
{
  *this = *this * xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator*=(const DirectX::XMFLOAT4& xm)
{
  *this = *this * xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator*=(const DirectX::XMFLOAT2A& xm)
{
  *this = *this * xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator*=(const DirectX::XMFLOAT3A& xm)
{
  *this = *this * xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator*=(const DirectX::XMFLOAT4A& xm)
{
  *this = *this * xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator*=(const DirectX::XMVECTOR& xm)
{
  *this = *this * xm;
  return *this;
}
template <class T>
template <class U>
inline Vec3<T> Vec3<T>::operator/(const U& v) const
{
  Vec3<T> vec(x, y, z);
  vec.x /= static_cast<T>(v);
  vec.y /= static_cast<T>(v);
  vec.z /= static_cast<T>(v);
  return vec;
}
template <class T>
template <class U>
inline Vec3<T> Vec3<T>::operator/(const Vec2<U>& vec2) const
{
  Vec3<T> vec(x, y, z);
  vec.x /= static_cast<T>(vec2.x);
  vec.y /= static_cast<T>(vec2.y);
  return vec;
}
template <class T>
template <class U>
inline Vec3<T> Vec3<T>::operator/(const Vec3<U>& vec3) const
{
  Vec3<T> vec(x, y, z);
  vec.x /= static_cast<T>(vec3.x);
  vec.y /= static_cast<T>(vec3.y);
  vec.z /= static_cast<T>(vec3.z);
  return vec;
}
template <class T>
template <class U>
inline Vec3<T> Vec3<T>::operator/(const Vec4<U>& vec4) const
{
  Vec3<T> vec(x, y, z);
  vec.x /= static_cast<T>(vec4.x);
  vec.y /= static_cast<T>(vec4.y);
  vec.z /= static_cast<T>(vec4.z);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator/(const DirectX::XMINT2& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x /= static_cast<T>(xm.x);
  vec.y /= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator/(const DirectX::XMINT3& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x /= static_cast<T>(xm.x);
  vec.y /= static_cast<T>(xm.y);
  vec.z /= static_cast<T>(xm.z);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator/(const DirectX::XMINT4& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x /= static_cast<T>(xm.x);
  vec.y /= static_cast<T>(xm.y);
  vec.z /= static_cast<T>(xm.z);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator/(const DirectX::XMUINT2& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x /= static_cast<T>(xm.x);
  vec.y /= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator/(const DirectX::XMUINT3& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x /= static_cast<T>(xm.x);
  vec.y /= static_cast<T>(xm.y);
  vec.z /= static_cast<T>(xm.z);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator/(const DirectX::XMUINT4& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x /= static_cast<T>(xm.x);
  vec.y /= static_cast<T>(xm.y);
  vec.z /= static_cast<T>(xm.z);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator/(const DirectX::XMFLOAT2& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x /= static_cast<T>(xm.x);
  vec.y /= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator/(const DirectX::XMFLOAT3& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x /= static_cast<T>(xm.x);
  vec.y /= static_cast<T>(xm.y);
  vec.z /= static_cast<T>(xm.z);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator/(const DirectX::XMFLOAT4& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x /= static_cast<T>(xm.x);
  vec.y /= static_cast<T>(xm.y);
  vec.z /= static_cast<T>(xm.z);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator/(const DirectX::XMFLOAT2A& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x /= static_cast<T>(xm.x);
  vec.y /= static_cast<T>(xm.y);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator/(const DirectX::XMFLOAT3A& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x /= static_cast<T>(xm.x);
  vec.y /= static_cast<T>(xm.y);
  vec.z /= static_cast<T>(xm.z);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator/(const DirectX::XMFLOAT4A& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x /= static_cast<T>(xm.x);
  vec.y /= static_cast<T>(xm.y);
  vec.z /= static_cast<T>(xm.z);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator/(const DirectX::XMVECTOR& xm) const
{
  Vec3<T> vec(x, y, z);
  vec.x /= static_cast<T>(DirectX::XMVectorGetX(xm));
  vec.y /= static_cast<T>(DirectX::XMVectorGetY(xm));
  vec.z /= static_cast<T>(DirectX::XMVectorGetZ(xm));
  return vec;
}
template <class T>
template <class U>
inline Vec3<T>& Vec3<T>::operator/=(const U& v)
{
  *this = *this / v;
  return *this;
}
template <class T>
template <class U>
inline Vec3<T>& Vec3<T>::operator/=(const Vec2<U>& vec2)
{
  *this = *this / vec2;
  return *this;
}
template <class T>
template <class U>
inline Vec3<T>& Vec3<T>::operator/=(const Vec3<U>& vec3)
{
  *this = *this / vec3;
  return *this;
}
template <class T>
template <class U>
inline Vec3<T>& Vec3<T>::operator/=(const Vec4<U>& vec4)
{
  *this = *this / vec4;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator/=(const DirectX::XMINT2& xm)
{
  *this = *this / xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator/=(const DirectX::XMINT3& xm)
{
  *this = *this / xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator/=(const DirectX::XMINT4& xm)
{
  *this = *this / xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator/=(const DirectX::XMUINT2& xm)
{
  *this = *this / xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator/=(const DirectX::XMUINT3& xm)
{
  *this = *this / xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator/=(const DirectX::XMUINT4& xm)
{
  *this = *this / xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator/=(const DirectX::XMFLOAT2& xm)
{
  *this = *this / xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator/=(const DirectX::XMFLOAT3& xm)
{
  *this = *this / xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator/=(const DirectX::XMFLOAT4& xm)
{
  *this = *this / xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator/=(const DirectX::XMFLOAT2A& xm)
{
  *this = *this / xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator/=(const DirectX::XMFLOAT3A& xm)
{
  *this = *this / xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator/=(const DirectX::XMFLOAT4A& xm)
{
  *this = *this / xm;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator/=(const DirectX::XMVECTOR& xm)
{
  *this = *this / xm;
  return *this;
}

template <class T>
template <class U>
inline bool Vec3<T>::operator==(const U& v) const
{
  return x == static_cast<T>(v) && y == static_cast<T>(v) && z == static_cast<T>(v);
}
template <class T>
template <class U>
inline bool Vec3<T>::operator==(const Vec2<U>& vec2) const
{
  return x == static_cast<T>(vec2.x) && y == static_cast<T>(vec2.y);
}
template <class T>
template <class U>
inline bool Vec3<T>::operator==(const Vec3<U>& vec3) const
{
  return x == static_cast<T>(vec3.x) && y == static_cast<T>(vec3.y) && z == static_cast<T>(vec3.z);
}
template <class T>
template <class U>
inline bool Vec3<T>::operator==(const Vec4<U>& vec4) const
{
  return x == static_cast<T>(vec4.x) && y == static_cast<T>(vec4.y) && z == static_cast<T>(vec4.z);
}
template <class T>
inline bool Vec3<T>::operator==(const DirectX::XMINT2& xm) const
{
  return x == static_cast<T>(xm.x) && y == static_cast<T>(xm.y);
}
template <class T>
inline bool Vec3<T>::operator==(const DirectX::XMINT3& xm) const
{
  return x == static_cast<T>(xm.x) && y == static_cast<T>(xm.y) && z == static_cast<T>(xm.z);
}
template <class T>
inline bool Vec3<T>::operator==(const DirectX::XMINT4& xm) const
{
  return x == static_cast<T>(xm.x) && y == static_cast<T>(xm.y) && z == static_cast<T>(xm.z);
}
template <class T>
inline bool Vec3<T>::operator==(const DirectX::XMUINT2& xm) const
{
  return x == static_cast<T>(xm.x) && y == static_cast<T>(xm.y);
}
template <class T>
inline bool Vec3<T>::operator==(const DirectX::XMUINT3& xm) const
{
  return x == static_cast<T>(xm.x) && y == static_cast<T>(xm.y) && z == static_cast<T>(xm.z);
}
template <class T>
inline bool Vec3<T>::operator==(const DirectX::XMUINT4& xm) const
{
  return x == static_cast<T>(xm.x) && y == static_cast<T>(xm.y) && z == static_cast<T>(xm.z);
}
template <class T>
inline bool Vec3<T>::operator==(const DirectX::XMFLOAT2& xm) const
{
  return x == static_cast<T>(xm.x) && y == static_cast<T>(xm.y);
}
template <class T>
inline bool Vec3<T>::operator==(const DirectX::XMFLOAT3& xm) const
{
  return x == static_cast<T>(xm.x) && y == static_cast<T>(xm.y) && z == static_cast<T>(xm.z);
}
template <class T>
inline bool Vec3<T>::operator==(const DirectX::XMFLOAT4& xm) const
{
  return x == static_cast<T>(xm.x) && y == static_cast<T>(xm.y) && z == static_cast<T>(xm.z);
}
template <class T>
inline bool Vec3<T>::operator==(const DirectX::XMFLOAT2A& xm) const
{
  return x == static_cast<T>(xm.x) && y == static_cast<T>(xm.y);
}
template <class T>
inline bool Vec3<T>::operator==(const DirectX::XMFLOAT3A& xm) const
{
  return x == static_cast<T>(xm.x) && y == static_cast<T>(xm.y) && z == static_cast<T>(xm.z);
}
template <class T>
inline bool Vec3<T>::operator==(const DirectX::XMFLOAT4A& xm) const
{
  return x == static_cast<T>(xm.x) && y == static_cast<T>(xm.y) && z == static_cast<T>(xm.z);
}
template <class T>
inline bool Vec3<T>::operator==(const DirectX::XMVECTOR& xm) const
{
  return x == static_cast<T>(DirectX ::XMVectorGetX(xm)) &&
         y == static_cast<T>(DirectX ::XMVectorGetY(xm)) &&
         z == static_cast<T>(DirectX ::XMVectorGetZ(xm));
}

// Bracket operator
template <class T>
inline T& Vec3<T>::operator[](unsigned int i)
{
  return data[i];
}
template <class T>
inline T Vec3<T>::operator[](unsigned int i) const
{
  return data[i];
}
#pragma endregion
#pragma region MatrixOperators
template <class T>
inline Vec3<T> Vec3<T>::operator*(const DirectX::XMMATRIX& mat) const
{
  Vec3<T> vec = DirectX::XMVector3Transform(Load(), mat);
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator*(const DirectX::XMFLOAT3X3 mat) const
{
  Vec3<T> vec = DirectX::XMVector3Transform(Load(), DirectX::XMLoadFloat3x3(&mat));
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator*(const DirectX::XMFLOAT4X4 mat) const
{
  Vec3<T> vec = DirectX::XMVector3Transform(Load(), DirectX::XMLoadFloat4x4(&mat));
  return vec;
}
template <class T>
inline Vec3<T> Vec3<T>::operator*(const DirectX::XMFLOAT4X4A mat) const
{
  Vec3<T> vec = DirectX::XMVector3Transform(Load(), DirectX::XMLoadFloat4x4A(&mat));
  return vec;
}
template <class T>
template <class U>
inline Vec3<T> Vec3<T>::operator*(const Mat3x3<U>& mat) const
{
  Vec3<T> vec = DirectX::XMVector3Transform(Load(), mat.Load());
  return vec;
}
template <class T>
template <class U>
inline Vec3<T> Vec3<T>::operator*(const Mat4x4<U>& mat) const
{
  Vec3<T> vec = DirectX::XMVector3Transform(Load(), mat.Load());
  return vec;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator*=(const DirectX::XMMATRIX& mat)
{
  *this = *this * mat;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator*=(const DirectX::XMFLOAT3X3 mat)
{
  *this = *this * mat;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator*=(const DirectX::XMFLOAT4X4 mat)
{
  *this = *this * mat;
  return *this;
}
template <class T>
inline Vec3<T>& Vec3<T>::operator*=(const DirectX::XMFLOAT4X4A mat)
{
  *this = *this * mat;
  return *this;
}
template <class T>
template <class U>
inline Vec3<T>& Vec3<T>::operator*=(const Mat3x3<U>& mat)
{
  *this = *this * mat;
  return *this;
}
template <class T>
template <class U>
inline Vec3<T>& Vec3<T>::operator*=(const Mat4x4<U>& mat)
{
  *this = *this * mat;
  return *this;
}
#pragma endregion
#pragma region Functions
template <class T>
inline DirectX::XMVECTOR Vec3<T>::Load() const
{
  DirectX::XMVECTOR v = DirectX::XMVectorZero();
  v                   = DirectX::XMVectorSetX(v, static_cast<float>(x));
  v                   = DirectX::XMVectorSetY(v, static_cast<float>(y));
  v                   = DirectX::XMVectorSetZ(v, static_cast<float>(z));
  v                   = DirectX::XMVectorSetW(v, static_cast<float>(0));
  return v;
}
template <class T>
template <class U>
inline DirectX::XMVECTOR Vec3<T>::Load(U w) const
{
  DirectX::XMVECTOR v = DirectX::XMVectorZero();
  v                   = DirectX::XMVectorSetX(v, static_cast<float>(x));
  v                   = DirectX::XMVectorSetY(v, static_cast<float>(y));
  v                   = DirectX::XMVectorSetZ(v, static_cast<float>(z));
  v                   = DirectX::XMVectorSetW(v, static_cast<float>(w));
  return v;
}
template <class T>
inline void Vec3<T>::Store(const DirectX::XMVECTOR& xm)
{
  x = static_cast<T>(DirectX::XMVectorGetX(xm));
  y = static_cast<T>(DirectX::XMVectorGetY(xm));
  z = static_cast<T>(DirectX::XMVectorGetZ(xm));
}

template <class T>
inline T Vec3<T>::Length() const
{
  return static_cast<T>(DirectX::XMVectorGetX(DirectX::XMVector3Length(Load())));
}
template <class T>
inline T Vec3<T>::LengthSq() const
{
  return static_cast<T>(DirectX::XMVectorGetX(DirectX::XMVector3LengthSq(Load())));
}
template <class T>
inline DirectX::XMINT2 Vec3<T>::AsXmInt2() const
{
  DirectX::XMINT2 v {};
  v.x = static_cast<int>(x);
  v.y = static_cast<int>(y);
  return v;
}
template <class T>
inline DirectX::XMINT3 Vec3<T>::AsXmInt3() const
{
  DirectX::XMINT3 v {};
  v.x = static_cast<int>(x);
  v.y = static_cast<int>(y);
  v.z = static_cast<int>(z);
  return v;
}
template <class T>
inline DirectX::XMINT4 Vec3<T>::AsXmInt4(int w) const
{
  DirectX::XMINT4 v {};
  v.x = static_cast<int>(x);
  v.y = static_cast<int>(y);
  v.z = static_cast<int>(z);
  v.w = w;
  return v;
}
template <class T>
inline DirectX::XMUINT2 Vec3<T>::AsXmUint2() const
{
  DirectX::XMUINT2 v {};
  v.x = static_cast<unsigned int>(x);
  v.y = static_cast<unsigned int>(y);
  return v;
}
template <class T>
inline DirectX::XMUINT3 Vec3<T>::AsXmUint3() const
{
  DirectX::XMUINT3 v {};
  v.x = static_cast<unsigned int>(x);
  v.y = static_cast<unsigned int>(y);
  v.z = static_cast<unsigned int>(z);
  return v;
}
template <class T>
inline DirectX::XMUINT4 Vec3<T>::AsXmUint4(unsigned int w) const
{
  DirectX::XMUINT4 v {};
  v.x = static_cast<unsigned int>(x);
  v.y = static_cast<unsigned int>(y);
  v.z = static_cast<unsigned int>(z);
  v.w = w;
  return v;
}
template <class T>
inline DirectX::XMFLOAT2 Vec3<T>::AsXmFloat2() const
{
  DirectX::XMFLOAT2 v {};
  v.x = static_cast<float>(x);
  v.y = static_cast<float>(y);
  return v;
}
template <class T>
inline DirectX::XMFLOAT3 Vec3<T>::AsXmFloat3() const
{
  DirectX::XMFLOAT3 v {};
  v.x = static_cast<float>(x);
  v.y = static_cast<float>(y);
  v.z = static_cast<float>(z);
  return v;
}
template <class T>
inline DirectX::XMFLOAT4 Vec3<T>::AsXmFloat4(float w) const
{
  DirectX::XMFLOAT4 v {};
  v.x = static_cast<float>(x);
  v.y = static_cast<float>(y);
  v.z = static_cast<float>(z);
  v.w = w;
  return v;
}
template <class T>
inline DirectX::XMFLOAT2A Vec3<T>::AsXmAsXmFloat2A() const
{
  DirectX::XMFLOAT2A v {};
  v.x = static_cast<float>(x);
  v.y = static_cast<float>(y);
  return v;
}
template <class T>
inline DirectX::XMFLOAT3A Vec3<T>::AsXmAsXmFloat3A() const
{
  DirectX::XMFLOAT3A v {};
  v.x = static_cast<float>(x);
  v.y = static_cast<float>(y);
  v.z = static_cast<float>(z);
  return v;
}
template <class T>
inline DirectX::XMFLOAT4A Vec3<T>::AsXmAsXmFloat4A(float w) const
{
  DirectX::XMFLOAT4A v {};
  v.x = static_cast<float>(x);
  v.y = static_cast<float>(y);
  v.z = static_cast<float>(z);
  v.w = w;
  return v;
}
template <class T>
inline Vec3<T> Vec3<T>::Abs() const
{
  Vec3<T> v = DirectX::XMVectorAbs(Load());
  return v;
}
template <class T>
inline Vec3<T> Vec3<T>::Normalize() const
{
  T       length = Length();
  Vec3<T> v(x / length, y / length, z / length);
  return v;
}
template <class T>
template <class U>
inline Vec3<T> Vec3<T>::Cross(const Vec3<U>& vec3) const
{
  Vec3<T> v = DirectX::XMVector3Cross(Load(), vec3.Load());
  return v;
}

template <class T>
inline Vec3<T> Vec3<T>::Cross(const DirectX::XMFLOAT3& xm) const
{
  Vec3<T> v = DirectX::XMVector3Cross(Load(), DirectX::XMLoadFloat3(&xm));
  return v;
}
template <class T>
inline Vec3<T> Vec3<T>::Cross(const DirectX::XMFLOAT3A& xm) const
{
  Vec3<T> v = DirectX::XMVector3Cross(Load(), DirectX::XMLoadFloat3A(&xm));
  return v;
}

template <class T>
inline Vec3<T> Vec3<T>::Cross(const DirectX::XMVECTOR& xm) const
{
  Vec3<T> v = DirectX::XMVector3Cross(Load(), xm);
  return v;
}

template <class T>
template <class U>
inline Mat3x3<T> Vec3<T>::GetRotationFrom(const Vec3<U>& vec3)
{
  Mat3x3<T> result;
  /*Vec3<T>     A    = *this;
  Vec3<U>     B    = vec3;
  Vec3<T>     axis = A.Cross(B);
  const float cosA = A.Dot(B);
  const float k    = 1.0f / (1.0f + cosA);

  result._11 = (axis.x * axis.x * k) + cosA;
  result._12 = (axis.y * axis.x * k) - axis.z;
  result._13 = (axis.z * axis.x * k) + axis.y;
  result._21 = (axis.x * axis.y * k) + axis.z;
  result._22 = (axis.y * axis.y * k) + cosA;
  result._23 = (axis.z * axis.y * k) - axis.x;
  result._31 = (axis.x * axis.z * k) - axis.y;
  result._32 = (axis.y * axis.z * k) + axis.x;
  result._33 = (axis.z * axis.z * k) + cosA;*/
  Vec3<T>   a  = vec3.Normalize();
  Vec3<T>   b  = Normalize();
  float     bl = vec3.Length();
  Vec3<T>   v  = a.Cross(b);
  float     s  = v.Length();
  float     c  = a.Dot(b);
  Mat3x3<T> vx;
  vx._11 = 0;
  vx._12 = -v[2];
  vx._13 = v[1];
  vx._21 = v[2];
  vx._22 = 0;
  vx._23 = -v[0];
  vx._31 = -v[1];
  vx._32 = v[0];
  vx._33 = 0;
  Mat3x3<T> r;
  if (s != 0)
    r = r + vx + vx * vx * ((1 - c) / std::pow(s, 2));
  return r;
}

template <class T>
template <class U>
inline float Vec3<T>::Dot(const Vec3<U>& vec3) const
{
  return DirectX::XMVectorGetX(DirectX::XMVector3Dot(Load(), vec3.Load()));
}
template <class T>
inline float Vec3<T>::Dot(const DirectX::XMINT3& xm) const
{
  return DirectX::XMVectorGetX(DirectX::XMVector3Dot(Load(), DirectX::XMLoadSInt3(&xm)));
}
template <class T>
inline float Vec3<T>::Dot(const DirectX::XMUINT3& xm) const
{
  return DirectX::XMVectorGetX(DirectX::XMVector3Dot(Load(), DirectX::XMLoadUInt3(&xm)));
}
template <class T>
inline float Vec3<T>::Dot(const DirectX::XMFLOAT3& xm) const
{
  return DirectX::XMVectorGetX(DirectX::XMVector3Dot(Load(), DirectX::XMLoadFloat3(&xm)));
}
template <class T>
inline float Vec3<T>::Dot(const DirectX::XMFLOAT3A& xm) const
{
  return DirectX::XMVectorGetX(DirectX::XMVector3Dot(Load(), DirectX::XMLoadFloat3A(&xm)));
}

template <class T>
template <class U>
inline float Vec3<T>::Angle(const Vec3<U>& Vec3) const
{
  return Angle(x * Vec3.x + y * Vec3.y + z * Vec3.z, LengthSq(), Vec3.LengthSq());
}
template <class T>
inline float Vec3<T>::Angle(const DirectX::XMINT3& xm) const
{
  return Angle(x * xm.x + y * xm.y + z * xm.z,
               LengthSq(),
               DirectX::XMVector3LengthSq(DirectX::XMLoadInt3(xm)));
}

template <class T>
inline float Vec3<T>::Angle(const DirectX::XMUINT3& xm) const
{
  return Angle(x * xm.x + y * xm.y + z * xm.z,
               LengthSq(),
               DirectX::XMVector3LengthSq(DirectX::XMLoadUInt3(xm)));
}

template <class T>
inline float Vec3<T>::Angle(const DirectX::XMFLOAT3& xm) const
{
  return Angle(x * xm.x + y * xm.y + z * xm.z,
               LengthSq(),
               DirectX::XMVector3LengthSq(DirectX::XMLoadFloat3(xm)));
}

template <class T>
inline float Vec3<T>::Angle(const DirectX::XMFLOAT3A& xm) const
{
  return Angle(x * xm.x + y * xm.y + z * xm.z,
               LengthSq(),
               DirectX::XMVector3LengthSq(DirectX::XMLoadFloat3A(xm)));
}

template <class T>
inline float Vec3<T>::Angle(float dot, float lenSq1, float lenSq2) const
{
  return acos(dot / sqrt(lenSq1 * lenSq2));
}

template <class T>
inline std::string Vec3<T>::ToString() const
{
  std::stringstream ss;
  ss << "[" << x << " " << y << " " << z << "]";
  return ss.str();
}

namespace std
{
  template <class T>
  struct hash<Vec3<T>>
  {
    size_t operator()(const Vec3<T>& p) const
    {
      size_t h = std::hash<T>()(p.x) ^ std::hash<T>()(p.y) ^ std::hash<T>()(p.z);
      return h;
    }
  };
} // namespace std
#pragma endregion