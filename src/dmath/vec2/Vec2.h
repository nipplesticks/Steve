#pragma once
#include <DirectXMath.h>
#include <string>

namespace DM
{
  template <class U>
  class Vec3;
  template <class U>
  class Vec4;
  template <class U>
  class Mat3x3;
  template <class U>
  class Mat4x4;
  template <class U>
  class Mat3x4;
  template <class U>
  class Mat4x3;

  template <class T>
  class Vec2
  {
  public:
#pragma region Constructors
    Vec2();
    template <class U>
    Vec2(U v);
    template <class U>
    Vec2(U x, U y);
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
#pragma endregion
#pragma region MatrixOperators
#pragma endregion
#pragma region Functions
    virtual DirectX::XMVECTOR Load() const                       = 0;
    virtual void              Store(const DirectX::XMVECTOR& xm) = 0;
    T                         Length() const;
    T                         LengthSq() const;
    DirectX::XMINT2           AsXmInt2() const;
    DirectX::XMINT3           AsXmInt3(int z = 0) const;
    DirectX::XMINT4           AsXmInt4(int z = 0, int w = 0) const;
    DirectX::XMUINT2          AsXmUint2() const;
    DirectX::XMUINT3          AsXmUint3(unsigned int z = 0u) const;
    DirectX::XMUINT4          AsXmUint4(unsigned int z = 0u, unsigned int w = 0) const;
    DirectX::XMFLOAT2         AsXmFloat2() const;
    DirectX::XMFLOAT3         AsXmFloat3(float z = 0.0f) const;
    DirectX::XMFLOAT4         AsXmFloat4(float z = 0.0f, float w = 0.0f) const;
    DirectX::XMFLOAT2A        AsXmAsXmFloat2A() const;
    DirectX::XMFLOAT3A        AsXmAsXmFloat3A(float z = 0.0f) const;
    DirectX::XMFLOAT4A        AsXmAsXmFloat4A(float z = 0.0f, float w = 0.0f) const;
    Vec2<T>                   Abs() const;
    Vec2<T>                   Normalize() const;
    template <class U>
    float               Dot(const Vec2<U>& vec2) const;
    float               Dot(const DirectX::XMINT2& xm) const;
    float               Dot(const DirectX::XMUINT2& xm) const;
    float               Dot(const DirectX::XMFLOAT2& xm) const;
    float               Dot(const DirectX::XMFLOAT2A& xm) const;
    virtual std::string ToString() const = 0;
#pragma endregion

  public:
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
  };
} // namespace DM