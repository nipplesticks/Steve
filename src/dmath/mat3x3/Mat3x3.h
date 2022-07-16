#pragma once
#include <DirectXMath.h>
#include <string>

template <class U>
class Mat4x4;
template <class U>
class Vec3;

template <class T>
class Mat3x3
{
public:
  Mat3x3();
  template <class U>
  Mat3x3(const Mat3x3<U>& mat);
  template <class U>
  Mat3x3(const Mat4x4<U>& mat);
  template <class U>
  Mat3x3(const Vec3<U>& r1, const Vec3<U>& r2, const Vec3<U>& r3);
  Mat3x3(const DirectX::XMFLOAT3X3& mat);
  Mat3x3(const DirectX::XMFLOAT4X4& mat);
  Mat3x3(const DirectX::XMFLOAT4X4A& mat);
  Mat3x3(const DirectX::XMMATRIX& mat);

  template <class U>
  Mat3x3<T>& operator=(const Mat3x3<U> mat);
  template <class U>
  Mat3x3<T>& operator=(const Mat4x4<U> mat);
  Mat3x3<T>& operator=(const DirectX::XMFLOAT3X3& mat);
  Mat3x3<T>& operator=(const DirectX::XMFLOAT4X4& mat);
  Mat3x3<T>& operator=(const DirectX::XMFLOAT4X4A& mat);
  Mat3x3<T>& operator=(const DirectX::XMMATRIX& mat);

  template <class U>
  Mat3x3<T> operator*(U v) const;
  template <class U>
  Mat3x3<T> operator*(const Mat4x4<U> mat) const;
  template <class U>
  Mat3x3<T> operator*(const Mat3x3<U> mat) const;
  Mat3x3<T> operator*(const DirectX::XMFLOAT3X3& mat) const;
  Mat3x3<T> operator*(const DirectX::XMFLOAT4X4& mat) const;
  Mat3x3<T> operator*(const DirectX::XMFLOAT4X4A& mat) const;
  Mat3x3<T> operator*(const DirectX::XMMATRIX& mat) const;

  template <class U>
  Mat3x3<T>& operator*=(U v);
  template <class U>
  Mat3x3<T>& operator*=(const Mat4x4<U> mat);
  template <class U>
  Mat3x3<T>& operator*=(const Mat3x3<U> mat);
  Mat3x3<T>& operator*=(const DirectX::XMFLOAT3X3& mat);
  Mat3x3<T>& operator*=(const DirectX::XMFLOAT4X4& mat);
  Mat3x3<T>& operator*=(const DirectX::XMFLOAT4X4A& mat);
  Mat3x3<T>& operator*=(const DirectX::XMMATRIX& mat);

  T& operator()(unsigned int x, unsigned int y);
  T  operator()(unsigned int x, unsigned int y) const;

  DirectX::XMMATRIX   Load() const;
  void                Store(const DirectX::XMMATRIX& mat);
  Mat3x3              Inverse() const;
  Mat3x3              Transpose() const;
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
      T _21;
      T _22;
      T _23;
      T _31;
      T _32;
      T _33;
    };
    T data[3][3];
  };
};
#include "../mat4x4/Mat4x4.h"
#include "../vec3/Vec3.h"
#pragma region FunctionDefinitions
template <class T>
inline Mat3x3<T>::Mat3x3()
{
  memset(&data[0][0], 0, sizeof(data));
  _11 = static_cast<T>(1);
  _22 = static_cast<T>(1);
  _33 = static_cast<T>(1);
}
template <class T>
template <class U>
inline Mat3x3<T>::Mat3x3(const Mat3x3<U>& mat)
{
  for (unsigned int i = 0; i < 3; i++)
    for (unsigned int j = 0; j < 3; j++)
      data[i][j] = static_cast<T>(mat.data[i][j]);
}
template <class T>
template <class U>
inline Mat3x3<T>::Mat3x3(const Mat4x4<U>& mat)
{
  memset(&data[0][0], 0, sizeof(data));
  for (unsigned int i = 0; i < 3; i++)
    for (unsigned int j = 0; j < 3; j++)
      data[i][j] = static_cast<T>(mat.data[i][j]);
}
template <class T>
template <class U>
inline Mat3x3<T>::Mat3x3(const Vec3<U>& r1, const Vec3<U>& r2, const Vec3<U>& r3)
{
  const Vec3<U>* m[] = {&r1, &r2, &r3};

  for (unsigned int i = 0; i < 3; i++)
    for (unsigned int j = 0; j < 3; j++)
      data[i][j] = static_cast<T>(m[i][j]);
}
template <class T>
inline Mat3x3<T>::Mat3x3(const DirectX::XMFLOAT3X3& mat)
{
  memset(&data[0][0], 0, sizeof(data));
  for (unsigned int i = 0; i < 3; i++)
    for (unsigned int j = 0; j < 3; j++)
      data[i][j] = static_cast<T>(mat.m[i][j]);
}
template <class T>
inline Mat3x3<T>::Mat3x3(const DirectX::XMFLOAT4X4& mat)
{
  for (unsigned int i = 0; i < 3; i++)
    for (unsigned int j = 0; j < 3; j++)
      data[i][j] = static_cast<T>(mat.m[i][j]);
}
template <class T>
inline Mat3x3<T>::Mat3x3(const DirectX::XMFLOAT4X4A& mat)
{
  for (unsigned int i = 0; i < 3; i++)
    for (unsigned int j = 0; j < 3; j++)
      data[i][j] = static_cast<T>(mat.m[i][j]);
}
template <class T>
inline Mat3x3<T>::Mat3x3(const DirectX::XMMATRIX& mat)
{
  DirectX::XMFLOAT4X4 m;
  DirectX::XMStoreFloat4x4(&m, mat);
  for (unsigned int i = 0; i < 3; i++)
    for (unsigned int j = 0; j < 3; j++)
      data[i][j] = static_cast<T>(m.m[i][j]);
}

template <class T>
template <class U>
inline Mat3x3<T>& Mat3x3<T>::operator=(const Mat3x3<U> mat)
{
  for (unsigned int i = 0; i < 3; i++)
    for (unsigned int j = 0; j < 3; j++)
      data[i][j] = static_cast<T>(mat.data[i][j]);
  return *this;
}
template <class T>
template <class U>
inline Mat3x3<T>& Mat3x3<T>::operator=(const Mat4x4<U> mat)
{
  memset(&data[0][0], 0, sizeof(data));
  for (unsigned int i = 0; i < 3; i++)
    for (unsigned int j = 0; j < 3; j++)
      data[i][j] = static_cast<T>(mat.data[i][j]);
  return *this;
}
template <class T>
inline Mat3x3<T>& Mat3x3<T>::operator=(const DirectX::XMFLOAT3X3& mat)
{
  memset(&data[0][0], 0, sizeof(data));
  for (unsigned int i = 0; i < 3; i++)
    for (unsigned int j = 0; j < 3; j++)
      data[i][j] = static_cast<T>(mat.m[i][j]);
  return *this;
}
template <class T>
inline Mat3x3<T>& Mat3x3<T>::operator=(const DirectX::XMFLOAT4X4& mat)
{
  for (unsigned int i = 0; i < 3; i++)
    for (unsigned int j = 0; j < 3; j++)
      data[i][j] = static_cast<T>(mat.m[i][j]);
  return *this;
}
template <class T>
inline Mat3x3<T>& Mat3x3<T>::operator=(const DirectX::XMFLOAT4X4A& mat)
{
  for (unsigned int i = 0; i < 3; i++)
    for (unsigned int j = 0; j < 3; j++)
      data[i][j] = static_cast<T>(mat.m[i][j]);
  return *this;
}
template <class T>
inline Mat3x3<T>& Mat3x3<T>::operator=(const DirectX::XMMATRIX& mat)
{
  DirectX::XMFLOAT4X4 m;
  DirectX::XMStoreFloat4x4(&m, mat);
  for (unsigned int i = 0; i < 3; i++)
    for (unsigned int j = 0; j < 3; j++)
      data[i][j] = static_cast<T>(m.m[i][j]);
  return *this;
}

template <class T>
template <class U>
inline Mat3x3<T> Mat3x3<T>::operator*(U v) const
{
  Mat3x3<T> m = *this;
  for (unsigned int i = 0; i < 3; i++)
    for (unsigned int j = 0; j < 3; j++)
      m(j, i) *= static_cast<T>(v);
  return m;
}
template <class T>
template <class U>
inline Mat3x3<T> Mat3x3<T>::operator*(const Mat3x3<U> mat) const
{
  Mat3x3<T> m = DirectX::XMMatrixMultiply(Load(), mat.Load());
  return m;
}
template <class T>
template <class U>
inline Mat3x3<T> Mat3x3<T>::operator*(const Mat4x4<U> mat) const
{
  Mat3x3<T> m = DirectX::XMMatrixMultiply(Load(), mat.Load());
  return m;
}
template <class T>
inline Mat3x3<T> Mat3x3<T>::operator*(const DirectX::XMFLOAT3X3& mat) const
{
  Mat3x3<T> m = DirectX::XMMatrixMultiply(Load(), DirectX::XMLoadFloat3x3(&mat));
  return m;
}
template <class T>
inline Mat3x3<T> Mat3x3<T>::operator*(const DirectX::XMFLOAT4X4& mat) const
{
  Mat3x3<T> m = DirectX::XMMatrixMultiply(Load(), DirectX::XMLoadFloat4x4(&mat));
  return m;
}
template <class T>
inline Mat3x3<T> Mat3x3<T>::operator*(const DirectX::XMFLOAT4X4A& mat) const
{
  Mat3x3<T> m = DirectX::XMMatrixMultiply(Load(), DirectX::XMLoadFloat4x4A(&mat));
  return m;
}
template <class T>
inline Mat3x3<T> Mat3x3<T>::operator*(const DirectX::XMMATRIX& mat) const
{
  Mat3x3<T> m = DirectX::XMMatrixMultiply(Load(), mat);
  return m;
}

template <class T>
template <class U>
inline Mat3x3<T>& Mat3x3<T>::operator*=(U v)
{
  *this = *this * v;
  return *this;
}
template <class T>
template <class U>
inline Mat3x3<T>& Mat3x3<T>::operator*=(const Mat3x3<U> mat)
{
  *this = *this * mat;
  return *this;
}
template <class T>
template <class U>
inline Mat3x3<T>& Mat3x3<T>::operator*=(const Mat4x4<U> mat)
{
  *this = *this * mat;
  return *this;
}
template <class T>
inline Mat3x3<T>& Mat3x3<T>::operator*=(const DirectX::XMFLOAT3X3& mat)
{
  *this = *this * mat;
  return *this;
}
template <class T>
inline Mat3x3<T>& Mat3x3<T>::operator*=(const DirectX::XMFLOAT4X4& mat)
{
  *this = *this * mat;
  return *this;
}
template <class T>
inline Mat3x3<T>& Mat3x3<T>::operator*=(const DirectX::XMFLOAT4X4A& mat)
{
  *this = *this * mat;
  return *this;
}
template <class T>
inline Mat3x3<T>& Mat3x3<T>::operator*=(const DirectX::XMMATRIX& mat)
{
  *this = *this * mat;
  return *this;
}
template <class T>
inline T& Mat3x3<T>::operator()(unsigned int x, unsigned int y)
{
  return data[y][x];
}
template <class T>
inline T Mat3x3<T>::operator()(unsigned int x, unsigned int y) const
{
  return data[y][x];
}
template <class T>
inline DirectX::XMMATRIX Mat3x3<T>::Load() const
{
  DirectX::XMFLOAT3X3 m;
  for (unsigned int i = 0; i < 3; i++)
    for (unsigned int j = 0; j < 3; j++)
      m.m[i][j] = static_cast<float>(data[i][j]);
  return DirectX::XMLoadFloat3x3(&m);
}
template <class T>
inline void Mat3x3<T>::Store(const DirectX::XMMATRIX& mat)
{
  *this = mat;
}

template <class T>
inline Mat3x3<T> Mat3x3<T>::Inverse() const
{
  Mat3x3<T> m;
  m.Store(DirectX::XMMatrixInverse(nullptr, Load()));
  return m;
}
template <class T>
inline Mat3x3<T> Mat3x3<T>::Transpose() const
{
  Mat3x3<T> m;
  m.Store(DirectX::XMMatrixTranspose(Load()));
  return m;
}

template <class T>
inline DirectX::XMFLOAT3X3 Mat3x3<T>::AsXmFloat3x3() const
{
  DirectX::XMFLOAT3X3 f;
  DirectX::XMStoreFloat3x3(&f, Load());
  return f;
}

template <class T>
inline DirectX::XMFLOAT4X4 Mat3x3<T>::AsXmFloat4x4() const
{
  DirectX::XMFLOAT4X4 f;
  DirectX::XMStoreFloat4x4(&f, Load());
  return f;
}
template <class T>
inline DirectX::XMFLOAT4X4 Mat3x3<T>::AsXmFloat4x4A() const
{
  DirectX::XMFLOAT4X4A f;
  DirectX::XMStoreFloat4x4(&f, Load());
  return f;
}
template <class T>
inline std::string Mat3x3<T>::ToString() const
{
  std::stringstream ss;
  for (unsigned int row = 0; row < 3; row++)
  {
    ss << "[" << data[row][0] << " " << data[row][1] << " " << data[row][2] << "]";
  }
  return ss.str();
}
#pragma endregion