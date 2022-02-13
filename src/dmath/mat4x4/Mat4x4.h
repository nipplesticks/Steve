#pragma once
#include <DirectXMath.h>
#include <string>

template <class U>
class Mat3x3;
template <class U>
class Vec4;
template <class T>
class Mat4x4
{
public:
  Mat4x4();
  template <class U>
  Mat4x4(const Mat4x4<U>& mat);
  template <class U>
  Mat4x4(const Mat3x3<U>& mat);
  template <class U>
  Mat4x4(const Vec4<U>& r1, const Vec4<U>& r2, const Vec4<U>& r3, const Vec4<U>& r4);
  Mat4x4(const DirectX::XMFLOAT3X3& mat);
  Mat4x4(const DirectX::XMFLOAT4X4& mat);
  Mat4x4(const DirectX::XMFLOAT4X4A& mat);
  Mat4x4(const DirectX::XMMATRIX& mat);

  template <class U>
  Mat4x4<T>& operator=(const Mat4x4<U> mat);
  template <class U>
  Mat4x4<T>& operator=(const Mat3x3<U> mat);
  Mat4x4<T>& operator=(const DirectX::XMFLOAT3X3& mat);
  Mat4x4<T>& operator=(const DirectX::XMFLOAT4X4& mat);
  Mat4x4<T>& operator=(const DirectX::XMFLOAT4X4A& mat);
  Mat4x4<T>& operator=(const DirectX::XMMATRIX& mat);

  template <class U>
  Mat4x4<T> operator*(U v) const;
  template <class U>
  Mat4x4<T> operator*(const Mat4x4<U> mat) const;
  template <class U>
  Mat4x4<T> operator*(const Mat3x3<U> mat) const;
  Mat4x4<T> operator*(const DirectX::XMFLOAT3X3& mat) const;
  Mat4x4<T> operator*(const DirectX::XMFLOAT4X4& mat) const;
  Mat4x4<T> operator*(const DirectX::XMFLOAT4X4A& mat) const;
  Mat4x4<T> operator*(const DirectX::XMMATRIX& mat) const;

  template <class U>
  Mat4x4<T>& operator*=(U v);
  template <class U>
  Mat4x4<T>& operator*=(const Mat4x4<U> mat);
  template <class U>
  Mat4x4<T>& operator*=(const Mat3x3<U> mat);
  Mat4x4<T>& operator*=(const DirectX::XMFLOAT3X3& mat);
  Mat4x4<T>& operator*=(const DirectX::XMFLOAT4X4& mat);
  Mat4x4<T>& operator*=(const DirectX::XMFLOAT4X4A& mat);
  Mat4x4<T>& operator*=(const DirectX::XMMATRIX& mat);

  T& operator()(unsigned int x, unsigned int y);
  T  operator()(unsigned int x, unsigned int y) const;

  DirectX::XMMATRIX   Load() const;
  void                Store(const DirectX::XMMATRIX& mat);
  Mat4x4              Inverse() const;
  Mat4x4              Transpose() const;
  DirectX::XMFLOAT3X3 AsXmFloat3x3() const;
  DirectX::XMFLOAT4X4 AsXmFloat4x4() const;
  DirectX::XMFLOAT4X4 AsXmFloat4x4A() const;

  std::string ToString() const;

public:
  union
  {
    struct
    {
      T _11;
      T _12;
      T _13;
      T _14;
      T _21;
      T _22;
      T _23;
      T _24;
      T _31;
      T _32;
      T _33;
      T _34;
      T _41;
      T _42;
      T _43;
      T _44;
    };
    T data[4][4];
  };
};
#include "../mat3x3/Mat3x3.h"
#include "../vec4/Vec4.h"
#pragma region functionDefinitions
template <class T>
inline Mat4x4<T>::Mat4x4()
{
  memset(&data[0][0], 0, sizeof(data));
  _11 = static_cast<T>(1);
  _22 = static_cast<T>(1);
  _33 = static_cast<T>(1);
  _44 = static_cast<T>(1);
}
template <class T>
template <class U>
inline Mat4x4<T>::Mat4x4(const Mat4x4<U>& mat)
{
  for (unsigned int i = 0; i < 4; i++)
    for (unsigned int j = 0; j < 4; j++)
      data[i][j] = static_cast<T>(mat.data[i][j]);
}
template <class T>
template <class U>
inline Mat4x4<T>::Mat4x4(const Mat3x3<U>& mat)
{
  memset(&data[0][0], 0, sizeof(data));
  for (unsigned int i = 0; i < 3; i++)
    for (unsigned int j = 0; j < 3; j++)
      data[i][j] = static_cast<T>(mat.data[i][j]);
  _44 = static_cast<T>(1);
}
template <class T>
template <class U>
inline Mat4x4<T>::Mat4x4(const Vec4<U>& r1, const Vec4<U>& r2, const Vec4<U>& r3, const Vec4<U>& r4)
{
  const Vec4<U>* m[] = {&r1, &r2, &r3, &r4};

  for (unsigned int i = 0; i < 4; i++)
    for (unsigned int j = 0; j < 4; j++)
      data[i][j] = static_cast<T>(m[i][j]);
}
template <class T>
inline Mat4x4<T>::Mat4x4(const DirectX::XMFLOAT3X3& mat)
{
  memset(&data[0][0], 0, sizeof(data));
  for (unsigned int i = 0; i < 3; i++)
    for (unsigned int j = 0; j < 3; j++)
      data[i][j] = static_cast<T>(mat.m[i][j]);
  _44 = static_cast<T>(1);
}
template <class T>
inline Mat4x4<T>::Mat4x4(const DirectX::XMFLOAT4X4& mat)
{
  for (unsigned int i = 0; i < 4; i++)
    for (unsigned int j = 0; j < 4; j++)
      data[i][j] = static_cast<T>(mat.m[i][j]);
}
template <class T>
inline Mat4x4<T>::Mat4x4(const DirectX::XMFLOAT4X4A& mat)
{
  for (unsigned int i = 0; i < 4; i++)
    for (unsigned int j = 0; j < 4; j++)
      data[i][j] = static_cast<T>(mat.m[i][j]);
}
template <class T>
inline Mat4x4<T>::Mat4x4(const DirectX::XMMATRIX& mat)
{
  DirectX::XMFLOAT4X4 m;
  DirectX::XMStoreFloat4x4(&m, mat);
  for (unsigned int i = 0; i < 4; i++)
    for (unsigned int j = 0; j < 4; j++)
      data[i][j] = static_cast<T>(m.m[i][j]);
}

template <class T>
template <class U>
inline Mat4x4<T>& Mat4x4<T>::operator=(const Mat4x4<U> mat)
{
  for (unsigned int i = 0; i < 4; i++)
    for (unsigned int j = 0; j < 4; j++)
      data[i][j] = static_cast<T>(mat.data[i][j]);
  return *this;
}
template <class T>
template <class U>
inline Mat4x4<T>& Mat4x4<T>::operator=(const Mat3x3<U> mat)
{
  memset(&data[0][0], 0, sizeof(data));
  for (unsigned int i = 0; i < 3; i++)
    for (unsigned int j = 0; j < 3; j++)
      data[i][j] = static_cast<T>(mat.data[i][j]);
  _44 = static_cast<T>(1);
  return *this;
}
template <class T>
inline Mat4x4<T>& Mat4x4<T>::operator=(const DirectX::XMFLOAT3X3& mat)
{
  memset(&data[0][0], 0, sizeof(data));
  for (unsigned int i = 0; i < 3; i++)
    for (unsigned int j = 0; j < 3; j++)
      data[i][j] = static_cast<T>(mat.m[i][j]);
  _44 = static_cast<T>(1);
  return *this;
}
template <class T>
inline Mat4x4<T>& Mat4x4<T>::operator=(const DirectX::XMFLOAT4X4& mat)
{
  for (unsigned int i = 0; i < 4; i++)
    for (unsigned int j = 0; j < 4; j++)
      data[i][j] = static_cast<T>(mat.m[i][j]);
  return *this;
}
template <class T>
inline Mat4x4<T>& Mat4x4<T>::operator=(const DirectX::XMFLOAT4X4A& mat)
{
  for (unsigned int i = 0; i < 4; i++)
    for (unsigned int j = 0; j < 4; j++)
      data[i][j] = static_cast<T>(mat.m[i][j]);
  return *this;
}
template <class T>
inline Mat4x4<T>& Mat4x4<T>::operator=(const DirectX::XMMATRIX& mat)
{
  DirectX::XMFLOAT4X4 m;
  DirectX::XMStoreFloat4x4(&m, mat);
  for (unsigned int i = 0; i < 4; i++)
    for (unsigned int j = 0; j < 4; j++)
      data[i][j] = static_cast<T>(m.m[i][j]);
  return *this;
}

template <class T>
template <class U>
inline Mat4x4<T> Mat4x4<T>::operator*(U v) const
{
  Mat4x4<T> m = *this;
  for (unsigned int i = 0; i < 4; i++)
    for (unsigned int j = 0; j < 4; j++)
      m(j, i) *= static_cast<T>(v);
  return m;
}
template <class T>
template <class U>
inline Mat4x4<T> Mat4x4<T>::operator*(const Mat4x4<U> mat) const
{
  Mat4x4<T> m = DirectX::XMMatrixMultiply(Load(), mat.Load());
  return m;
}
template <class T>
template <class U>
inline Mat4x4<T> Mat4x4<T>::operator*(const Mat3x3<U> mat) const
{
  Mat4x4<T> m = DirectX::XMMatrixMultiply(Load(), mat.Load());
  return m;
}
template <class T>
inline Mat4x4<T> Mat4x4<T>::operator*(const DirectX::XMFLOAT3X3& mat) const
{
  Mat4x4<T> m = DirectX::XMMatrixMultiply(Load(), DirectX::XMLoadFloat3x3(&mat));
  return m;
}
template <class T>
inline Mat4x4<T> Mat4x4<T>::operator*(const DirectX::XMFLOAT4X4& mat) const
{
  Mat4x4<T> m = DirectX::XMMatrixMultiply(Load(), DirectX::XMLoadFloat4x4(&mat));
  return m;
}
template <class T>
inline Mat4x4<T> Mat4x4<T>::operator*(const DirectX::XMFLOAT4X4A& mat) const
{
  Mat4x4<T> m = DirectX::XMMatrixMultiply(Load(), DirectX::XMLoadFloat4x4A(&mat));
  return m;
}
template <class T>
inline Mat4x4<T> Mat4x4<T>::operator*(const DirectX::XMMATRIX& mat) const
{
  Mat4x4<T> m = DirectX::XMMatrixMultiply(Load(), mat);
  return m;
}

template <class T>
template <class U>
inline Mat4x4<T>& Mat4x4<T>::operator*=(U v)
{
  *this = *this * v;
  return *this;
}
template <class T>
template <class U>
inline Mat4x4<T>& Mat4x4<T>::operator*=(const Mat4x4<U> mat)
{
  *this = *this * mat;
  return *this;
}
template <class T>
template <class U>
inline Mat4x4<T>& Mat4x4<T>::operator*=(const Mat3x3<U> mat)
{
  *this = *this * mat;
  return *this;
}
template <class T>
inline Mat4x4<T>& Mat4x4<T>::operator*=(const DirectX::XMFLOAT3X3& mat)
{
  *this = *this * mat;
  return *this;
}
template <class T>
inline Mat4x4<T>& Mat4x4<T>::operator*=(const DirectX::XMFLOAT4X4& mat)
{
  *this = *this * mat;
  return *this;
}
template <class T>
inline Mat4x4<T>& Mat4x4<T>::operator*=(const DirectX::XMFLOAT4X4A& mat)
{
  *this = *this * mat;
  return *this;
}
template <class T>
inline Mat4x4<T>& Mat4x4<T>::operator*=(const DirectX::XMMATRIX& mat)
{
  *this = *this * mat;
  return *this;
}
template <class T>
inline T& Mat4x4<T>::operator()(unsigned int x, unsigned int y)
{
  return data[y][x];
}
template <class T>
inline T Mat4x4<T>::operator()(unsigned int x, unsigned int y) const
{
  return data[y][x];
}
template <class T>
inline DirectX::XMMATRIX Mat4x4<T>::Load() const
{
  DirectX::XMFLOAT4X4 m;
  for (unsigned int i = 0; i < 4; i++)
    for (unsigned int j = 0; j < 4; j++)
      m.m[i][j] = static_cast<float>(data[i][j]);
  return DirectX::XMLoadFloat4x4(&m);
}
template <class T>
inline void Mat4x4<T>::Store(const DirectX::XMMATRIX& mat)
{
  *this = mat;
}

template <class T>
inline Mat4x4<T> Mat4x4<T>::Inverse() const
{
  Mat4x4<T> m;
  m.Store(DirectX::XMMatrixInverse(nullptr, Load()));
  return m;
}
template <class T>
inline Mat4x4<T> Mat4x4<T>::Transpose() const
{
  Mat4x4<T> m;
  m.Store(DirectX::XMMatrixTranspose(Load()));
  return m;
}

template <class T>
inline DirectX::XMFLOAT3X3 Mat4x4<T>::AsXmFloat3x3() const
{
  DirectX::XMFLOAT3X3 f;
  DirectX::XMStoreFloat3x3(&f, Load());
  return f;
}

template <class T>
inline DirectX::XMFLOAT4X4 Mat4x4<T>::AsXmFloat4x4() const
{
  DirectX::XMFLOAT4X4 f;
  DirectX::XMStoreFloat4x4(&f, Load());
  return f;
}
template <class T>
inline DirectX::XMFLOAT4X4 Mat4x4<T>::AsXmFloat4x4A() const
{
  DirectX::XMFLOAT4X4A f;
  DirectX::XMStoreFloat4x4(&f, Load());
  return f;
}
template <class T>
inline std::string Mat4x4<T>::ToString() const
{
  std::stringstream ss;
  for (unsigned int row = 0; row < 4; row++)
  {
    ss << "[" << data[row][0] << " " << data[row][1] << " " << data[row][2] << " " << data[row][3]
       << "]";
  }
  return ss.str();
}
#pragma endregion