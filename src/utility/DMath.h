#pragma once
#include <DirectXMath.h>
#include <cstddef>
#include <string>

namespace DM
{
  struct Mat3x3
  {
  public:
#pragma region Constructors
    Mat3x3()
    {
      Store(DirectX::XMMatrixIdentity());
    }
    Mat3x3(const DirectX::XMFLOAT3X3& _mat)
    {
      m_mat = _mat;
    }
    Mat3x3(const Mat3x3& _mat)
    {
      m_mat = _mat.m_mat;
    }
#pragma endregion

#pragma region Mat Operators
    Mat3x3& operator=(const Mat3x3& other)
    {
      if (this != &other)
      {
        m_mat = other.m_mat;
      }

      return *this;
    }
    Mat3x3& operator=(const DirectX::XMFLOAT3X3& other)
    {
      m_mat = other;

      return *this;
    }
    Mat3x3 operator*(const Mat3x3& other)
    {
      Mat3x3 val;

      val.Store(DirectX::XMMatrixMultiply(Load(), other.Load()));

      return val;
    }
    Mat3x3 operator*(const DirectX::XMFLOAT3X3& other)
    {
      Mat3x3 val;

      val.Store(DirectX::XMMatrixMultiply(Load(), DirectX::XMLoadFloat3x3(&other)));

      return val;
    }
    Mat3x3& operator*=(const Mat3x3& other)
    {
      *this = *this * other;

      return *this;
    }
    Mat3x3& operator*=(const DirectX::XMFLOAT3X3& other)
    {
      *this = *this * other;

      return *this;
    }
    
#pragma endregion

#pragma region Functions

    DirectX::XMMATRIX Load() const
    {
      return DirectX::XMLoadFloat3x3(&m_mat);
    }

    void Store(const DirectX::XMMATRIX& _mat)
    {
      DirectX::XMStoreFloat3x3(&m_mat, _mat);
    }

    Mat3x3 Inverse()
    {
      Mat3x3 val;

      val.Store(DirectX::XMMatrixInverse(nullptr, Load()));

      return val;
    }

    Mat3x3 Transpose()
    {
      Mat3x3 val;

      val.Store(DirectX::XMMatrixTranspose(Load()));

      return val;
    }

    const DirectX::XMFLOAT3X3& AsXmFloat3x3()
    {
      return m_mat;
    }

    std::string ToString() const
    {
      std::string str = "";

      for (size_t y = 0; y < 3; y++)
      {
        for (size_t x = 0; x < 3; x++)
        {
          str += "[" + std::to_string(x + 1) + std::to_string(y + 1) +
                 "]: " + std::to_string(m_mat(x, y)) + ", ";
        }
        str.pop_back();
        str[str.size() - 1] = '\n';
      }

      return str;
    }

#pragma endregion

    union
    {
      struct
      {
        float _11;
        float _12;
        float _13;
        float _21;
        float _22;
        float _23;
        float _31;
        float _32;
        float _33;
      };
      DirectX::XMFLOAT3X3 m_mat;
    };
  };

  struct Mat4x4
  {
  public:
#pragma region Constructors
    Mat4x4()
    {
      Store(DirectX::XMMatrixIdentity());
    }
    Mat4x4(const DirectX::XMFLOAT4X4& _mat)
    {
      m_mat = _mat;
    }
    Mat4x4(const Mat4x4& _mat)
    {
      m_mat = _mat.m_mat;
    }
#pragma endregion

#pragma region Mat Operators
    Mat4x4& operator=(const Mat4x4& other)
    {
      if (this != &other)
      {
        m_mat = other.m_mat;
      }

      return *this;
    }
    Mat4x4& operator=(const DirectX::XMFLOAT4X4& other)
    {
      m_mat = other;

      return *this;
    }
    Mat4x4 operator*(const Mat4x4& other)
    {
      Mat4x4 val;

      val.Store(DirectX::XMMatrixMultiply(Load(), other.Load()));

      return val;
    }
    Mat4x4 operator*(const DirectX::XMFLOAT4X4& other)
    {
      Mat4x4 val;

      val.Store(DirectX::XMMatrixMultiply(Load(), DirectX::XMLoadFloat4x4(&other)));

      return val;
    }
    Mat4x4& operator*=(const Mat4x4& other)
    {
      *this = *this * other;

      return *this;
    }
    Mat4x4& operator*=(const DirectX::XMFLOAT4X4& other)
    {
      *this = *this * other;

      return *this;
    }
#pragma endregion

#pragma region Functions

    DirectX::XMMATRIX Load() const
    {
      return DirectX::XMLoadFloat4x4(&m_mat);
    }

    void Store(const DirectX::XMMATRIX& _mat)
    {
      DirectX::XMStoreFloat4x4(&m_mat, _mat);
    }

    Mat4x4 Inverse()
    {
      Mat4x4 val;

      val.Store(DirectX::XMMatrixInverse(nullptr, Load()));

      return val;
    }

    Mat4x4 Transpose()
    {
      Mat4x4 val;

      val.Store(DirectX::XMMatrixTranspose(Load()));

      return val;
    }

    const DirectX::XMFLOAT4X4& AsXmFloat4x4()
    {
      return m_mat;
    }

    std::string ToString() const
    {
      std::string str = "";

      for (size_t y = 0; y < 4; y++)
      {
        for (size_t x = 0; x < 4; x++)
        {
          str += "[" + std::to_string(x + 1) + std::to_string(y + 1) +
                 "]: " + std::to_string(m_mat(x, y)) + ", ";
        }
        str.pop_back();
        str[str.size() - 1] = '\n';
      }

      return str;
    }

#pragma endregion

    union
    {
      struct
      {
        float _11;
        float _12;
        float _13;
        float _14;
        float _21;
        float _22;
        float _23;
        float _24;
        float _31;
        float _32;
        float _33;
        float _34;
        float _41;
        float _42;
        float _43;
        float _44;
      };
      DirectX::XMFLOAT4X4 m_mat;
    };
  };

  struct Vec2f
  {
  public:
#pragma region Constructors
    Vec2f(float _x = 0.0f, float _y = 0.0f)
    {
      m_vec.x = _x;
      m_vec.y = _y;
    }

    Vec2f(const DirectX::XMFLOAT2& _xmFlt)
    {
      m_vec = _xmFlt;
    }

    Vec2f(const Vec2f& _vec2)
    {
      m_vec = _vec2.m_vec;
    }

#pragma endregion

#pragma region Vector Operators

    Vec2f& operator=(const Vec2f& _vec2f)
    {
      if (this != &_vec2f)
      {
        m_vec = _vec2f.m_vec;
      }

      return *this;
    }

    Vec2f& operator=(const DirectX::XMFLOAT2& _xmFlt)
    {
      m_vec = _xmFlt;

      return *this;
    }

    Vec2f operator+(const DirectX::XMVECTOR& _xmVec) const
    {
      Vec2f sum;

      sum.Store(DirectX::XMVectorAdd(Load(), _xmVec));

      return sum;
    }

    Vec2f operator-(const DirectX::XMVECTOR& _xmVec) const
    {
      Vec2f sum;

      sum.Store(DirectX::XMVectorSubtract(Load(), _xmVec));

      return sum;
    }

    Vec2f operator*(const DirectX::XMVECTOR& _xmVec)
    {
      Vec2f product;

      product.Store(DirectX::XMVectorMultiply(Load(), _xmVec));

      return product;
    }

    Vec2f operator/(const DirectX::XMVECTOR& _xmVec)
    {
      Vec2f product;

      product.Store(DirectX::XMVectorDivide(Load(), _xmVec));

      return product;
    }

    Vec2f operator+(const Vec2f& _vec2f) const
    {
      Vec2f sum;

      sum.Store(DirectX::XMVectorAdd(Load(), _vec2f.Load()));

      return sum;
    }

    Vec2f operator+(const DirectX::XMFLOAT2& _xmFlt) const
    {
      Vec2f sum;

      sum.Store(DirectX::XMVectorAdd(Load(), DirectX::XMLoadFloat2(&_xmFlt)));

      return sum;
    }

    Vec2f operator-(const Vec2f& _vec2f) const
    {
      Vec2f sum;

      sum.Store(DirectX::XMVectorSubtract(Load(), _vec2f.Load()));

      return sum;
    }

    Vec2f operator-(const DirectX::XMFLOAT2& _xmFlt) const
    {
      Vec2f sum;

      sum.Store(DirectX::XMVectorSubtract(Load(), DirectX::XMLoadFloat2(&_xmFlt)));

      return sum;
    }

    Vec2f operator*(const Vec2f& _vec2f) const
    {
      Vec2f product;

      product.Store(DirectX::XMVectorMultiply(Load(), _vec2f.Load()));

      return product;
    }

    Vec2f operator*(const DirectX::XMFLOAT2& _xmFlt) const
    {
      Vec2f product;

      product.Store(DirectX::XMVectorMultiply(Load(), DirectX::XMLoadFloat2(&m_vec)));

      return product;
    }

    Vec2f operator/(const Vec2f& _vec2f) const
    {
      Vec2f product;

      product.Store(DirectX::XMVectorDivide(Load(), _vec2f.Load()));

      return product;
    }

    Vec2f operator/(const DirectX::XMFLOAT2& _xmFlt) const
    {
      Vec2f product;

      product.Store(DirectX::XMVectorDivide(Load(), DirectX::XMLoadFloat2(&m_vec)));

      return product;
    }

    Vec2f operator*(float m)
    {
      Vec2f product;

      product.Store(DirectX::XMVectorScale(Load(), m));

      return product;
    }

    Vec2f operator*(int m)
    {
      Vec2f product;

      product.Store(DirectX::XMVectorScale(Load(), (float)m));

      return product;
    }

    Vec2f& operator*=(float m)
    {
      Store(DirectX::XMVectorScale(Load(), m));

      return *this;
    }

    Vec2f& operator*=(int m)
    {
      Store(DirectX::XMVectorScale(Load(), (float)m));

      return *this;
    }

    Vec2f operator/(float m)
    {
      Vec2f product;

      product.Store(DirectX::XMVectorScale(Load(), 1.0f / m));

      return product;
    }

    Vec2f operator/(int m)
    {
      Vec2f product;

      product.Store(DirectX::XMVectorScale(Load(), 1.0f / (float)m));

      return product;
    }

    Vec2f& operator/=(float m)
    {
      Store(DirectX::XMVectorScale(Load(), 1.0f / m));

      return *this;
    }

    Vec2f& operator/=(int m)
    {
      Store(DirectX::XMVectorScale(Load(), 1.0f / (float)m));

      return *this;
    }

    Vec2f& operator+=(const Vec2f& _vec2f)
    {
      *this = *this + _vec2f;

      return *this;
    }

    Vec2f& operator+=(const DirectX::XMFLOAT2& _xmFlt)
    {
      *this = *this + _xmFlt;

      return *this;
    }

    Vec2f& operator+=(const DirectX::XMVECTOR& _xmVec)
    {
      *this = *this + _xmVec;

      return *this;
    }

    Vec2f& operator-=(const Vec2f& _vec2f)
    {
      *this = *this - _vec2f;

      return *this;
    }

    Vec2f& operator-=(const DirectX::XMFLOAT2& _xmFlt)
    {
      *this = *this - _xmFlt;

      return *this;
    }

    Vec2f& operator-=(const DirectX::XMVECTOR& _xmVec)
    {
      *this = *this - _xmVec;

      return *this;
    }

    Vec2f& operator*=(const Vec2f& _vec2f)
    {
      *this = *this * _vec2f;

      return *this;
    }

    Vec2f& operator*=(const DirectX::XMFLOAT2& _xmFlt)
    {
      *this = *this * _xmFlt;

      return *this;
    }

    Vec2f& operator*=(const DirectX::XMVECTOR& _xmVec)
    {
      *this = *this * _xmVec;

      return *this;
    }

    Vec2f& operator/=(const Vec2f& _vec2f)
    {
      *this = *this / _vec2f;

      return *this;
    }

    Vec2f& operator/=(const DirectX::XMFLOAT2& _xmFlt)
    {
      *this = *this / _xmFlt;

      return *this;
    }

    Vec2f& operator/=(const DirectX::XMVECTOR& _xmVec)
    {
      *this = *this / _xmVec;

      return *this;
    }

    bool operator==(const Vec2f& _vec2f) const
    {
      static float EPSILON = 0.0001f;

      Vec2f rest = (*this - _vec2f).Abs();

      return rest.x < EPSILON && rest.y < EPSILON;
    }

    bool operator==(const DirectX::XMFLOAT2& _xmFlt) const
    {
      static float EPSILON = 0.0001f;

      Vec2f rest = (*this - _xmFlt).Abs();

      return rest.x < EPSILON && rest.y < EPSILON;
    }

    bool operator==(const DirectX::XMVECTOR& _xmVec) const
    {
      static float EPSILON = 0.0001f;

      Vec2f rest = (*this - _xmVec).Abs();

      return rest.x < EPSILON && rest.y < EPSILON;
    }

#pragma endregion

#pragma region Matrix Operators
    Vec2f operator*(const DirectX::XMMATRIX& _matrix)
    {
      Vec2f val;

      val.Store(DirectX::XMVector2Transform(Load(), _matrix));

      return val;
    }

    Vec2f operator*(const DirectX::XMFLOAT4X4& _matrix)
    {
      return *this * DirectX::XMLoadFloat4x4(&_matrix);
    }

    Vec2f operator*(const DirectX::XMFLOAT3X3& _matrix)
    {
      return *this * DirectX::XMLoadFloat3x3(&_matrix);
    }
#pragma endregion

#pragma region Functions

    DirectX::XMVECTOR Load() const
    {
      return DirectX::XMLoadFloat2(&m_vec);
    }

    void Store(const DirectX::XMVECTOR& vector)
    {
      DirectX::XMStoreFloat2(&m_vec, vector);
    }

    const DirectX::XMFLOAT2& AsXmFloat2() const
    {
      return m_vec;
    }

    DirectX::XMFLOAT3 AsXmFloat3() const
    {
      DirectX::XMFLOAT3 val;
      val.x = x;
      val.y = y;
      val.z = 0.0f;

      return val;
    }

    DirectX::XMFLOAT4 AsXmFloat4() const
    {
      DirectX::XMFLOAT4 val;
      val.x = x;
      val.y = y;
      val.z = 0.0f;
      val.w = 0.0f;

      return val;
    }

    DirectX::XMINT2 AsXmInt2() const
    {
      DirectX::XMINT2 val;
      val.x = (int)x;
      val.y = (int)y;

      return val;
    }

    DirectX::XMINT3 AsXmInt3() const
    {
      DirectX::XMINT3 val;
      val.x = (int)x;
      val.y = (int)y;
      val.z = 0;

      return val;
    }

    DirectX::XMINT4 AsXmInt4() const
    {
      DirectX::XMINT4 val;
      val.x = (int)x;
      val.y = (int)y;
      val.z = 0;
      val.w = 0;

      return val;
    }

    Vec2f Abs() const
    {
      return Vec2f(fabsf(x), fabsf(y));
    }

    Vec2f Normalize() const
    {
      Vec2f nor;

      nor.Store(DirectX::XMVector2Normalize(Load()));

      return nor;
    }

    Vec2f Round() const
    {
      Vec2f val;
      val.Store(DirectX::XMVectorRound(Load()));
      return val;
    }

    DirectX::XMFLOAT3 Cross(const DirectX::XMVECTOR& vector)
    {
      DirectX::XMFLOAT3 val;
      DirectX::XMStoreFloat3(&val, DirectX::XMVector3Cross(Load(), vector));
      return val;
    }

    DirectX::XMFLOAT3 Cross(const Vec2f& _Vec2f)
    {
      DirectX::XMFLOAT3 val;
      DirectX::XMStoreFloat3(&val, DirectX::XMVector3Cross(Load(), _Vec2f.Load()));
      return val;
    }

    DirectX::XMFLOAT3 Cross(const DirectX::XMFLOAT3& _xmFlt)
    {
      DirectX::XMFLOAT3 val;
      DirectX::XMStoreFloat3(&val, DirectX::XMVector3Cross(Load(), DirectX::XMLoadFloat3(&_xmFlt)));
      return val;
    }

    float Dot(const DirectX::XMVECTOR& vector)
    {
      return DirectX::XMVectorGetX(DirectX::XMVector2Dot(Load(), vector));
    }

    float Dot(const Vec2f& _Vec2f)
    {
      return DirectX::XMVectorGetX(DirectX::XMVector2Dot(Load(), _Vec2f.Load()));
    }

    float Dot(const DirectX::XMFLOAT2& _xmFlt)
    {
      return DirectX::XMVectorGetX(DirectX::XMVector2Dot(Load(), DirectX::XMLoadFloat2(&_xmFlt)));
    }

    float Length() const
    {
      return DirectX::XMVectorGetX(DirectX::XMVector2Length(Load()));
    }

    float LengthSq() const
    {
      return DirectX::XMVectorGetX(DirectX::XMVector2LengthSq(Load()));
    }

    std::string ToString() const
    {
      std::string str = "X: " + std::to_string(x) + ", " + "Y: " + std::to_string(y);
      return str;
    }
#pragma endregion

    union
    {
      struct
      {
        float x;
        float y;
      };
      DirectX::XMFLOAT2 m_vec;
    };
  };

  struct Vec3f
  {
  public:
#pragma region Constructors
    Vec3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f)
    {
      m_vec.x = _x;
      m_vec.y = _y;
      m_vec.z = _z;
    }

    Vec3f(const DirectX::XMFLOAT3& _xmFlt)
    {
      m_vec = _xmFlt;
    }

    Vec3f(const DirectX::XMFLOAT4A& _xmFlt)
    {
      m_vec.x = _xmFlt.x;
      m_vec.y = _xmFlt.y;
      m_vec.z = _xmFlt.z;
    }
    Vec3f(const DirectX::XMFLOAT4& _xmFlt)
    {
      m_vec.x = _xmFlt.x;
      m_vec.y = _xmFlt.y;
      m_vec.z = _xmFlt.z;
    }

    Vec3f(const Vec3f& _vec3)
    {
      m_vec = _vec3.m_vec;
    }

#pragma endregion

#pragma region Vector Operators

    Vec3f& operator=(const Vec3f& _Vec3f)
    {
      if (this != &_Vec3f)
      {
        m_vec = _Vec3f.m_vec;
      }

      return *this;
    }
    
    Vec3f& operator=(const DirectX::XMFLOAT4A& _xmFlt)
    {
      m_vec.x = _xmFlt.x;
      m_vec.y = _xmFlt.y;
      m_vec.z = _xmFlt.z;
      return *this;
    }
    Vec3f& operator=(const DirectX::XMFLOAT4& _xmFlt)
    {
      m_vec.x = _xmFlt.x;
      m_vec.y = _xmFlt.y;
      m_vec.z = _xmFlt.z;
      return *this;
    }
    Vec3f& operator=(const DirectX::XMFLOAT3& _xmFlt)
    {
      m_vec = _xmFlt;

      return *this;
    }

    Vec3f operator+(const DirectX::XMVECTOR& _xmVec) const
    {
      Vec3f sum;

      sum.Store(DirectX::XMVectorAdd(Load(), _xmVec));

      return sum;
    }

    Vec3f operator-(const DirectX::XMVECTOR& _xmVec) const
    {
      Vec3f sum;

      sum.Store(DirectX::XMVectorSubtract(Load(), _xmVec));

      return sum;
    }

    Vec3f operator*(const DirectX::XMVECTOR& _xmVec)
    {
      Vec3f product;

      product.Store(DirectX::XMVectorMultiply(Load(), _xmVec));

      return product;
    }

    Vec3f operator/(const DirectX::XMVECTOR& _xmVec)
    {
      Vec3f product;

      product.Store(DirectX::XMVectorDivide(Load(), _xmVec));

      return product;
    }

    Vec3f operator+(const Vec3f& _Vec3f) const
    {
      Vec3f sum;

      sum.Store(DirectX::XMVectorAdd(Load(), _Vec3f.Load()));

      return sum;
    }

    Vec3f operator+(const DirectX::XMFLOAT3& _xmFlt) const
    {
      Vec3f sum;

      sum.Store(DirectX::XMVectorAdd(Load(), DirectX::XMLoadFloat3(&_xmFlt)));

      return sum;
    }

    Vec3f operator-(const Vec3f& _Vec3f) const
    {
      Vec3f sum;

      sum.Store(DirectX::XMVectorSubtract(Load(), _Vec3f.Load()));

      return sum;
    }

    Vec3f operator-(const DirectX::XMFLOAT3& _xmFlt) const
    {
      Vec3f sum;

      sum.Store(DirectX::XMVectorSubtract(Load(), DirectX::XMLoadFloat3(&_xmFlt)));

      return sum;
    }

    Vec3f operator*(const Vec3f& _Vec3f) const
    {
      Vec3f product;

      product.Store(DirectX::XMVectorMultiply(Load(), _Vec3f.Load()));

      return product;
    }

    Vec3f operator*(const DirectX::XMFLOAT3& _xmFlt) const
    {
      Vec3f product;

      product.Store(DirectX::XMVectorMultiply(Load(), DirectX::XMLoadFloat3(&m_vec)));

      return product;
    }

    Vec3f operator/(const Vec3f& _Vec3f) const
    {
      Vec3f product;

      product.Store(DirectX::XMVectorDivide(Load(), _Vec3f.Load()));

      return product;
    }

    Vec3f operator/(const DirectX::XMFLOAT3& _xmFlt) const
    {
      Vec3f product;

      product.Store(DirectX::XMVectorDivide(Load(), DirectX::XMLoadFloat3(&m_vec)));

      return product;
    }

    Vec3f operator*(float m)
    {
      Vec3f product;

      product.Store(DirectX::XMVectorScale(Load(), m));

      return product;
    }

    Vec3f operator*(int m)
    {
      Vec3f product;

      product.Store(DirectX::XMVectorScale(Load(), (float)m));

      return product;
    }

    Vec3f& operator*=(float m)
    {
      Store(DirectX::XMVectorScale(Load(), m));

      return *this;
    }

    Vec3f& operator*=(int m)
    {
      Store(DirectX::XMVectorScale(Load(), (float)m));

      return *this;
    }

    Vec3f operator/(float m)
    {
      Vec3f product;

      product.Store(DirectX::XMVectorScale(Load(), 1.0f / m));

      return product;
    }

    Vec3f operator/(int m)
    {
      Vec3f product;

      product.Store(DirectX::XMVectorScale(Load(), 1.0f / (float)m));

      return product;
    }

    Vec3f& operator/=(float m)
    {
      Store(DirectX::XMVectorScale(Load(), 1.0f / m));

      return *this;
    }

    Vec3f& operator/=(int m)
    {
      Store(DirectX::XMVectorScale(Load(), 1.0f / (float)m));

      return *this;
    }

    Vec3f& operator+=(const Vec3f& _Vec3f)
    {
      *this = *this + _Vec3f;

      return *this;
    }

    Vec3f& operator+=(const DirectX::XMFLOAT3& _xmFlt)
    {
      *this = *this + _xmFlt;

      return *this;
    }

    Vec3f& operator+=(const DirectX::XMVECTOR& _xmVec)
    {
      *this = *this + _xmVec;

      return *this;
    }

    Vec3f& operator-=(const Vec3f& _Vec3f)
    {
      *this = *this - _Vec3f;

      return *this;
    }

    Vec3f& operator-=(const DirectX::XMFLOAT3& _xmFlt)
    {
      *this = *this - _xmFlt;

      return *this;
    }

    Vec3f& operator-=(const DirectX::XMVECTOR& _xmVec)
    {
      *this = *this - _xmVec;

      return *this;
    }

    Vec3f& operator*=(const Vec3f& _Vec3f)
    {
      *this = *this * _Vec3f;

      return *this;
    }

    Vec3f& operator*=(const DirectX::XMFLOAT3& _xmFlt)
    {
      *this = *this * _xmFlt;

      return *this;
    }

    Vec3f& operator*=(const DirectX::XMVECTOR& _xmVec)
    {
      *this = *this * _xmVec;

      return *this;
    }

    Vec3f& operator/=(const Vec3f& _Vec3f)
    {
      *this = *this / _Vec3f;

      return *this;
    }

    Vec3f& operator/=(const DirectX::XMFLOAT3& _xmFlt)
    {
      *this = *this / _xmFlt;

      return *this;
    }

    Vec3f& operator/=(const DirectX::XMVECTOR& _xmVec)
    {
      *this = *this / _xmVec;

      return *this;
    }

    bool operator==(const Vec3f& _Vec3f) const
    {
      static float EPSILON = 0.0001f;

      Vec3f rest = (*this - _Vec3f).Abs();

      return rest.x < EPSILON && rest.y < EPSILON && rest.z < EPSILON;
    }

    bool operator==(const DirectX::XMFLOAT3& _xmFlt) const
    {
      static float EPSILON = 0.0001f;

      Vec3f rest = (*this - _xmFlt).Abs();

      return rest.x < EPSILON && rest.y < EPSILON;
    }

    bool operator==(const DirectX::XMVECTOR& _xmVec) const
    {
      static float EPSILON = 0.0001f;

      Vec3f rest = (*this - _xmVec).Abs();

      return rest.x < EPSILON && rest.y < EPSILON;
    }

    bool operator<(const Vec3f& _Vec3f) const
    {
      return memcmp((void*)this, (void*)&_Vec3f, sizeof(Vec3f)) > 0;
    }

#pragma endregion

#pragma region Matrix Operators
    Vec3f operator*(const DirectX::XMMATRIX& _matrix)
    {
      Vec3f val;

      val.Store(DirectX::XMVector3Transform(Load(), _matrix));

      return val;
    }

    Vec3f operator*(const DirectX::XMFLOAT4X4& _matrix)
    {
      return *this * DirectX::XMLoadFloat4x4(&_matrix);
    }

    Vec3f operator*(const DirectX::XMFLOAT3X3& _matrix)
    {
      return *this * DirectX::XMLoadFloat3x3(&_matrix);
    }
#pragma endregion

#pragma region Functions

    DirectX::XMVECTOR Load() const
    {
      return DirectX::XMLoadFloat3(&m_vec);
    }

    DirectX::XMVECTOR LoadAsVec4(float w) const
    {
      return DirectX::XMVectorSet(x, y, z, w);
    }

    void Store(const DirectX::XMVECTOR& vector)
    {
      DirectX::XMStoreFloat3(&m_vec, vector);
    }

    DirectX::XMFLOAT2 AsXmFloat2() const
    {
      DirectX::XMFLOAT2 val;
      val.x = x;
      val.y = y;

      return val;
    }

    DirectX::XMFLOAT4A AsXmFloat4APoint() const
    {
      DirectX::XMFLOAT4A xmFloat = {};

      xmFloat.x = x;
      xmFloat.y = y;
      xmFloat.z = z;
      xmFloat.w = 1.0f;
      return xmFloat;
    }

    DirectX::XMFLOAT4A AsXmFloat4AVector() const
    {
      DirectX::XMFLOAT4A xmFloat = {};

      xmFloat.x = x;
      xmFloat.y = y;
      xmFloat.z = z;
      xmFloat.w = 0.0f;
      return xmFloat;
    }

    const DirectX::XMFLOAT3& AsXmFloat3() const
    {
      return m_vec;
    }

    DirectX::XMFLOAT4 AsXmFloat4() const
    {
      DirectX::XMFLOAT4 val;
      val.x = x;
      val.y = y;
      val.z = z;
      val.w = 0.0f;

      return val;
    }

    DirectX::XMINT2 AsXmInt2() const
    {
      DirectX::XMINT2 val;
      val.x = (int)x;
      val.y = (int)y;

      return val;
    }

    DirectX::XMINT3 AsXmInt3() const
    {
      DirectX::XMINT3 val;
      val.x = (int)x;
      val.y = (int)y;
      val.z = (int)z;

      return val;
    }

    DirectX::XMINT4 AsXmInt4() const
    {
      DirectX::XMINT4 val;
      val.x = (int)x;
      val.y = (int)y;
      val.z = (int)z;
      val.w = 0;

      return val;
    }

    Vec3f Abs() const
    {
      return Vec3f(fabsf(x), fabsf(y), fabsf(z));
    }

    Vec3f Normalize() const
    {
      Vec3f nor;

      nor.Store(DirectX::XMVector3Normalize(Load()));

      return nor;
    }

    Vec3f Round() const
    {
      Vec3f val;
      val.Store(DirectX::XMVectorRound(Load()));
      return val;
    }

    Vec3f Cross(const DirectX::XMVECTOR& vector) const
    {
      Vec3f val;
      val.Store(DirectX::XMVector3Cross(Load(), vector));
      return val;
    }

    Vec3f Cross(const Vec3f& _Vec3f) const
    {
      Vec3f val;
      val.Store(DirectX::XMVector3Cross(Load(), _Vec3f.Load()));
      return val;
    }

    Vec3f Cross(const DirectX::XMFLOAT3& _xmFlt) const
    {
      Vec3f val;
      val.Store(DirectX::XMVector3Cross(Load(), DirectX::XMLoadFloat3(&_xmFlt)));
      return val;
    }

    float Dot(const DirectX::XMVECTOR& vector) const
    {
      return DirectX::XMVectorGetX(DirectX::XMVector3Dot(Load(), vector));
    }

    float Dot(const Vec3f& _Vec3f) const
    {
      return DirectX::XMVectorGetX(DirectX::XMVector3Dot(Load(), _Vec3f.Load()));
    }

    float Dot(const DirectX::XMFLOAT3& _xmFlt) const
    {
      return DirectX::XMVectorGetX(DirectX::XMVector3Dot(Load(), DirectX::XMLoadFloat3(&_xmFlt)));
    }

    float Length() const
    {
      return DirectX::XMVectorGetX(DirectX::XMVector3Length(Load()));
    }

    float LengthSq() const
    {
      return DirectX::XMVectorGetX(DirectX::XMVector3LengthSq(Load()));
    }

    std::string ToString() const
    {
      char str[128];
      size_t printCount = sprintf_s(&str[0], 128, "[%f, %f, %f]", x, y, z);
      str[printCount]   = '\0';
      /*std::string str = "X: " + std::to_string(x) + ", " + "Y: " + std::to_string(y) + ", " +
                        "Z: " + std::to_string(z);*/

      return str;
    }
#pragma endregion
    union
    {
      struct
      {
        float x;
        float y;
        float z;
      };
      DirectX::XMFLOAT3 m_vec;
    };

  private:
  };

  struct Vec4f
  {
  public:
#pragma region Constructors
    Vec4f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f, float _w = 0.0f)
    {
      m_vec.x = _x;
      m_vec.y = _y;
      m_vec.z = _z;
      m_vec.w = _w;
    }

    Vec4f(const DirectX::XMFLOAT4& _xmFlt)
    {
      m_vec = _xmFlt;
    }

    Vec4f(const Vec4f& _vec4)
    {
      m_vec = _vec4.m_vec;
    }

#pragma endregion

#pragma region Vector Operators

    Vec4f& operator=(const Vec4f& _Vec4f)
    {
      if (this != &_Vec4f)
      {
        m_vec = _Vec4f.m_vec;
      }

      return *this;
    }

    Vec4f& operator=(const DirectX::XMFLOAT4& _xmFlt)
    {
      m_vec = _xmFlt;

      return *this;
    }

    Vec4f operator+(const DirectX::XMVECTOR& _xmVec) const
    {
      Vec4f sum;

      sum.Store(DirectX::XMVectorAdd(Load(), _xmVec));

      return sum;
    }

    Vec4f operator-(const DirectX::XMVECTOR& _xmVec) const
    {
      Vec4f sum;

      sum.Store(DirectX::XMVectorSubtract(Load(), _xmVec));

      return sum;
    }

    Vec4f operator*(const DirectX::XMVECTOR& _xmVec)
    {
      Vec4f product;

      product.Store(DirectX::XMVectorMultiply(Load(), _xmVec));

      return product;
    }

    Vec4f operator/(const DirectX::XMVECTOR& _xmVec)
    {
      Vec4f product;

      product.Store(DirectX::XMVectorDivide(Load(), _xmVec));

      return product;
    }

    Vec4f operator+(const Vec4f& _Vec4f) const
    {
      Vec4f sum;

      sum.Store(DirectX::XMVectorAdd(Load(), _Vec4f.Load()));

      return sum;
    }

    Vec4f operator+(const DirectX::XMFLOAT4& _xmFlt) const
    {
      Vec4f sum;

      sum.Store(DirectX::XMVectorAdd(Load(), DirectX::XMLoadFloat4(&_xmFlt)));

      return sum;
    }

    Vec4f operator-(const Vec4f& _Vec4f) const
    {
      Vec4f sum;

      sum.Store(DirectX::XMVectorSubtract(Load(), _Vec4f.Load()));

      return sum;
    }

    Vec4f operator-(const DirectX::XMFLOAT4& _xmFlt) const
    {
      Vec4f sum;

      sum.Store(DirectX::XMVectorSubtract(Load(), DirectX::XMLoadFloat4(&_xmFlt)));

      return sum;
    }

    Vec4f operator*(const Vec4f& _Vec4f) const
    {
      Vec4f product;

      product.Store(DirectX::XMVectorMultiply(Load(), _Vec4f.Load()));

      return product;
    }

    Vec4f operator*(const DirectX::XMFLOAT4& _xmFlt) const
    {
      Vec4f product;

      product.Store(DirectX::XMVectorMultiply(Load(), DirectX::XMLoadFloat4(&m_vec)));

      return product;
    }

    Vec4f operator/(const Vec4f& _Vec4f) const
    {
      Vec4f product;

      product.Store(DirectX::XMVectorDivide(Load(), _Vec4f.Load()));

      return product;
    }

    Vec4f operator/(const DirectX::XMFLOAT4& _xmFlt) const
    {
      Vec4f product;

      product.Store(DirectX::XMVectorDivide(Load(), DirectX::XMLoadFloat4(&m_vec)));

      return product;
    }

    Vec4f operator*(float m)
    {
      Vec4f product;

      product.Store(DirectX::XMVectorScale(Load(), m));

      return product;
    }

    Vec4f operator*(int m)
    {
      Vec4f product;

      product.Store(DirectX::XMVectorScale(Load(), (float)m));

      return product;
    }

    Vec4f& operator*=(float m)
    {
      Store(DirectX::XMVectorScale(Load(), m));

      return *this;
    }

    Vec4f& operator*=(int m)
    {
      Store(DirectX::XMVectorScale(Load(), (float)m));

      return *this;
    }

    Vec4f operator/(float m)
    {
      Vec4f product;

      product.Store(DirectX::XMVectorScale(Load(), 1.0f / m));

      return product;
    }

    Vec4f operator/(int m)
    {
      Vec4f product;

      product.Store(DirectX::XMVectorScale(Load(), 1.0f / (float)m));

      return product;
    }

    Vec4f& operator/=(float m)
    {
      Store(DirectX::XMVectorScale(Load(), 1.0f / m));

      return *this;
    }

    Vec4f& operator/=(int m)
    {
      Store(DirectX::XMVectorScale(Load(), 1.0f / (float)m));

      return *this;
    }

    Vec4f& operator+=(const Vec4f& _Vec4f)
    {
      *this = *this + _Vec4f;

      return *this;
    }

    Vec4f& operator+=(const DirectX::XMFLOAT4& _xmFlt)
    {
      *this = *this + _xmFlt;

      return *this;
    }

    Vec4f& operator+=(const DirectX::XMVECTOR& _xmVec)
    {
      *this = *this + _xmVec;

      return *this;
    }

    Vec4f& operator-=(const Vec4f& _Vec4f)
    {
      *this = *this - _Vec4f;

      return *this;
    }

    Vec4f& operator-=(const DirectX::XMFLOAT4& _xmFlt)
    {
      *this = *this - _xmFlt;

      return *this;
    }

    Vec4f& operator-=(const DirectX::XMVECTOR& _xmVec)
    {
      *this = *this - _xmVec;

      return *this;
    }

    Vec4f& operator*=(const Vec4f& _Vec4f)
    {
      *this = *this * _Vec4f;

      return *this;
    }

    Vec4f& operator*=(const DirectX::XMFLOAT4& _xmFlt)
    {
      *this = *this * _xmFlt;

      return *this;
    }

    Vec4f& operator*=(const DirectX::XMVECTOR& _xmVec)
    {
      *this = *this * _xmVec;

      return *this;
    }

    Vec4f& operator/=(const Vec4f& _Vec4f)
    {
      *this = *this / _Vec4f;

      return *this;
    }

    Vec4f& operator/=(const DirectX::XMFLOAT4& _xmFlt)
    {
      *this = *this / _xmFlt;

      return *this;
    }

    Vec4f& operator/=(const DirectX::XMVECTOR& _xmVec)
    {
      *this = *this / _xmVec;

      return *this;
    }

    bool operator==(const Vec4f& _Vec4f) const
    {
      static float EPSILON = 0.0001f;

      Vec4f rest = (*this - _Vec4f).Abs();

      return rest.x < EPSILON && rest.y < EPSILON;
    }

    bool operator==(const DirectX::XMFLOAT4& _xmFlt) const
    {
      static float EPSILON = 0.0001f;

      Vec4f rest = (*this - _xmFlt).Abs();

      return rest.x < EPSILON && rest.y < EPSILON;
    }

    bool operator==(const DirectX::XMVECTOR& _xmVec) const
    {
      static float EPSILON = 0.0001f;

      Vec4f rest = (*this - _xmVec).Abs();

      return rest.x < EPSILON && rest.y < EPSILON;
    }

#pragma endregion

#pragma region Matrix Operators
    Vec4f operator*(const DirectX::XMMATRIX& _matrix)
    {
      Vec4f val;

      val.Store(DirectX::XMVector3Transform(Load(), _matrix));

      return val;
    }

    Vec4f operator*(const DirectX::XMFLOAT4X4& _matrix)
    {
      return *this * DirectX::XMLoadFloat4x4(&_matrix);
    }

    Vec4f operator*(const DirectX::XMFLOAT3X3& _matrix)
    {
      return *this * DirectX::XMLoadFloat3x3(&_matrix);
    }
#pragma endregion

#pragma region Functions

    DirectX::XMVECTOR Load() const
    {
      return DirectX::XMLoadFloat4(&m_vec);
    }

    void Store(const DirectX::XMVECTOR& vector)
    {
      DirectX::XMStoreFloat4(&m_vec, vector);
    }

    DirectX::XMFLOAT2 AsXmFloat2() const
    {
      DirectX::XMFLOAT2 val;
      val.x = x;
      val.y = y;

      return val;
    }

    DirectX::XMFLOAT3& AsXmFloat3() const
    {
      DirectX::XMFLOAT3 val;
      val.x = x;
      val.y = y;
      val.z = z;

      return val;
    }

    const DirectX::XMFLOAT4& AsXmFloat4() const
    {
      return m_vec;
    }

    DirectX::XMINT2 AsXmInt2() const
    {
      DirectX::XMINT2 val;
      val.x = (int)x;
      val.y = (int)y;

      return val;
    }

    DirectX::XMINT3 AsXmInt3() const
    {
      DirectX::XMINT3 val;
      val.x = (int)x;
      val.y = (int)y;
      val.z = (int)z;

      return val;
    }

    DirectX::XMINT4 AsXmInt4() const
    {
      DirectX::XMINT4 val;
      val.x = (int)x;
      val.y = (int)y;
      val.z = (int)z;
      val.w = (int)w;

      return val;
    }

    Vec4f Abs() const
    {
      return Vec4f(fabsf(x), fabsf(y), fabsf(z));
    }

    Vec4f Normalize() const
    {
      Vec4f nor;

      nor.Store(DirectX::XMVector4Normalize(Load()));

      return nor;
    }

    Vec4f Round() const
    {
      Vec4f val;
      val.Store(DirectX::XMVectorRound(Load()));
      return val;
    }

    Vec4f Cross(const DirectX::XMVECTOR& vector)
    {
      Vec4f val;
      val.Store(DirectX::XMVector3Cross(Load(), vector));
      return val;
    }

    Vec4f Cross(const Vec4f& _Vec3f)
    {
      Vec4f val;
      val.Store(DirectX::XMVector3Cross(Load(), _Vec3f.Load()));
      return val;
    }

    Vec4f Cross(const DirectX::XMFLOAT4& _xmFlt)
    {
      Vec4f val;
      val.Store(DirectX::XMVector3Cross(Load(), DirectX::XMLoadFloat4(&_xmFlt)));
      return val;
    }

    float Dot(const DirectX::XMVECTOR& vector)
    {
      return DirectX::XMVectorGetX(DirectX::XMVector3Dot(Load(), vector));
    }

    float Dot(const Vec3f& _Vec3f)
    {
      return DirectX::XMVectorGetX(DirectX::XMVector3Dot(Load(), _Vec3f.Load()));
    }

    float Dot(const DirectX::XMFLOAT4& _xmFlt)
    {
      return DirectX::XMVectorGetX(DirectX::XMVector3Dot(Load(), DirectX::XMLoadFloat4(&_xmFlt)));
    }

    float Length(bool skipW = false) const
    {
      if (!skipW)
        return DirectX::XMVectorGetX(DirectX::XMVector4Length(Load()));
      else
        return DirectX::XMVectorGetX(DirectX::XMVector3Length(Load()));
    }

    float LengthSq() const
    {
      return DirectX::XMVectorGetX(DirectX::XMVector4LengthSq(Load()));
    }

    std::string ToString() const
    {
      std::string str = "X: " + std::to_string(x) + ", " + "Y: " + std::to_string(y) + ", " +
                        "Z: " + std::to_string(z) + ", " + "W: " + std::to_string(w);
      return str;
    }
#pragma endregion

    union
    {
      struct
      {
        float x;
        float y;
        float z;
        float w;
      };
      DirectX::XMFLOAT4 m_vec;
    };
  };

  struct Vec2i
  {
  public:
#pragma region Constructors
    Vec2i(int _x = 0, int _y = 0)
    {
      m_vec.x = _x;
      m_vec.y = _y;
    }

    Vec2i(const DirectX::XMINT2& _xmInt)
    {
      m_vec = _xmInt;
    }

    Vec2i(const Vec2i& _vec2)
    {
      m_vec = _vec2.m_vec;
    }

#pragma endregion

#pragma region Vector Operators

    Vec2i& operator=(const Vec2i& _Vec2i)
    {
      if (this != &_Vec2i)
      {
        m_vec = _Vec2i.m_vec;
      }

      return *this;
    }

    Vec2i& operator=(const DirectX::XMINT2& _xmInt)
    {
      m_vec = _xmInt;

      return *this;
    }

    Vec2i operator+(const DirectX::XMVECTOR& _xmVec) const
    {
      Vec2i sum;

      sum.Store(DirectX::XMVectorAdd(Load(), _xmVec));

      return sum;
    }

    Vec2i operator-(const DirectX::XMVECTOR& _xmVec) const
    {
      Vec2i sum;

      sum.Store(DirectX::XMVectorSubtract(Load(), _xmVec));

      return sum;
    }

    Vec2i operator*(const DirectX::XMVECTOR& _xmVec)
    {
      Vec2i product;

      product.Store(DirectX::XMVectorMultiply(Load(), _xmVec));

      return product;
    }

    Vec2i operator/(const DirectX::XMVECTOR& _xmVec)
    {
      Vec2i product;

      product.Store(DirectX::XMVectorDivide(Load(), _xmVec));

      return product;
    }

    Vec2i operator+(const Vec2i& _Vec2i) const
    {
      Vec2i sum;

      sum.Store(DirectX::XMVectorAdd(Load(), _Vec2i.Load()));

      return sum;
    }

    Vec2i operator+(const DirectX::XMINT2& _xmInt) const
    {
      Vec2i sum;

      sum.Store(DirectX::XMVectorAdd(Load(), DirectX::XMLoadSInt2(&_xmInt)));

      return sum;
    }

    Vec2i operator-(const Vec2i& _Vec2i) const
    {
      Vec2i sum;

      sum.Store(DirectX::XMVectorSubtract(Load(), _Vec2i.Load()));

      return sum;
    }

    Vec2i operator-(const DirectX::XMINT2& _xmInt) const
    {
      Vec2i sum;

      sum.Store(DirectX::XMVectorSubtract(Load(), DirectX::XMLoadSInt2(&_xmInt)));

      return sum;
    }

    Vec2i operator*(const Vec2i& _Vec2i) const
    {
      Vec2i product;

      product.Store(DirectX::XMVectorMultiply(Load(), _Vec2i.Load()));

      return product;
    }

    Vec2i operator*(const DirectX::XMINT2& _xmInt) const
    {
      Vec2i product;

      product.Store(DirectX::XMVectorMultiply(Load(), DirectX::XMLoadSInt2(&m_vec)));

      return product;
    }

    Vec2i operator/(const Vec2i& _Vec2i) const
    {
      Vec2i product;

      product.Store(DirectX::XMVectorDivide(Load(), _Vec2i.Load()));

      return product;
    }

    Vec2i operator/(const DirectX::XMINT2& _xmInt) const
    {
      Vec2i product;

      product.Store(DirectX::XMVectorDivide(Load(), DirectX::XMLoadSInt2(&m_vec)));

      return product;
    }

    Vec2i operator*(int m)
    {
      Vec2f product;

      product.Store(DirectX::XMVectorScale(Load(), (float)m));

      return product.Round().AsXmInt2();
    }

    Vec2i& operator*=(int m)
    {
      Vec2f product;

      product.Store(DirectX::XMVectorScale(Load(), (float)m));

      *this = product.Round().AsXmInt2();

      return *this;
    }

    Vec2i operator/(int m)
    {
      Vec2f product;

      product.Store(DirectX::XMVectorScale(Load(), 1.0f / (float)m));

      return product.Round().AsXmInt2();
    }

    Vec2i& operator/=(int m)
    {
      Vec2f product;

      product.Store(DirectX::XMVectorScale(Load(), 1.0f / (float)m));

      *this = product.Round().AsXmInt2();

      return *this;
    }

    Vec2i& operator+=(const Vec2i& _Vec2i)
    {
      *this = *this + _Vec2i;

      return *this;
    }

    Vec2i& operator+=(const DirectX::XMINT2& _xmInt)
    {
      *this = *this + _xmInt;

      return *this;
    }

    Vec2i& operator+=(const DirectX::XMVECTOR& _xmVec)
    {
      *this = *this + _xmVec;

      return *this;
    }

    Vec2i& operator-=(const Vec2i& _Vec2i)
    {
      *this = *this - _Vec2i;

      return *this;
    }

    Vec2i& operator-=(const DirectX::XMINT2& _xmInt)
    {
      *this = *this - _xmInt;

      return *this;
    }

    Vec2i& operator-=(const DirectX::XMVECTOR& _xmVec)
    {
      *this = *this - _xmVec;

      return *this;
    }

    Vec2i& operator*=(const Vec2i& _Vec2i)
    {
      *this = *this * _Vec2i;

      return *this;
    }

    Vec2i& operator*=(const DirectX::XMINT2& _xmInt)
    {
      *this = *this * _xmInt;

      return *this;
    }

    Vec2i& operator*=(const DirectX::XMVECTOR& _xmVec)
    {
      *this = *this * _xmVec;

      return *this;
    }

    Vec2i& operator/=(const Vec2i& _Vec2i)
    {
      *this = *this / _Vec2i;

      return *this;
    }

    Vec2i& operator/=(const DirectX::XMINT2& _xmInt)
    {
      *this = *this / _xmInt;

      return *this;
    }

    Vec2i& operator/=(const DirectX::XMVECTOR& _xmVec)
    {
      *this = *this / _xmVec;

      return *this;
    }

    bool operator==(const Vec2i& _Vec2i) const
    {
      return x == _Vec2i.x && y == _Vec2i.y;
    }

    bool operator==(const DirectX::XMINT2& _xmInt) const
    {
      return x == _xmInt.x && y == _xmInt.y;
    }

    bool operator==(const DirectX::XMVECTOR& _xmVec) const
    {
      static float EPSILON = 0.0001f;

      Vec2i val;
      val.Store(_xmVec);

      return *this == val;
    }

#pragma endregion

#pragma region Matrix Operators
    Vec2i operator*(const DirectX::XMMATRIX& _matrix)
    {
      Vec2f val;
      Vec2i iVal;

      val.Store(DirectX::XMVector2Transform(Load(), _matrix));

      iVal = val.Round().AsXmInt2();

      return iVal;
    }

    Vec2i operator*(const DirectX::XMFLOAT4X4& _matrix)
    {
      return *this * DirectX::XMLoadFloat4x4(&_matrix);
    }

    Vec2i operator*(const DirectX::XMFLOAT3X3& _matrix)
    {
      return *this * DirectX::XMLoadFloat3x3(&_matrix);
    }
#pragma endregion

#pragma region Functions

    DirectX::XMVECTOR Load() const
    {
      return DirectX::XMLoadSInt2(&m_vec);
    }

    void Store(const DirectX::XMVECTOR& vector)
    {
      DirectX::XMStoreSInt2(&m_vec, vector);
    }

    DirectX::XMFLOAT2 AsXmFloat2() const
    {
      DirectX::XMFLOAT2 val;
      val.x = (float)x;
      val.y = (float)y;
      return val;
    }

    DirectX::XMFLOAT3 AsXmFloat3() const
    {
      DirectX::XMFLOAT3 val;
      val.x = (float)x;
      val.y = (float)y;
      val.z = 0.0f;

      return val;
    }

    DirectX::XMFLOAT4 AsXmFloat4() const
    {
      DirectX::XMFLOAT4 val;
      val.x = (float)x;
      val.y = (float)y;
      val.z = 0.0f;
      val.w = 0.0f;

      return val;
    }

    const DirectX::XMINT2& AsXmInt2() const
    {
      return m_vec;
    }

    DirectX::XMINT3 AsXmInt3() const
    {
      DirectX::XMINT3 val;
      val.x = x;
      val.y = y;
      val.z = 0;

      return val;
    }

    DirectX::XMINT4 AsXmInt4() const
    {
      DirectX::XMINT4 val;
      val.x = x;
      val.y = y;
      val.z = 0;
      val.w = 0;

      return val;
    }

    Vec2i Abs() const
    {
      return Vec2i(abs(x), abs(y));
    }

    Vec2f Normalize() const
    {
      Vec2f nor;

      nor.Store(DirectX::XMVector2Normalize(Load()));

      return nor;
    }

    DirectX::XMINT3 Cross(const DirectX::XMVECTOR& vector)
    {
      Vec3f fVal = AsXmFloat3();
      return fVal.Cross(vector).Round().AsXmInt3();
    }

    DirectX::XMINT3 Cross(const Vec2i& _Vec2i)
    {
      Vec3f fVal = AsXmFloat3();
      return fVal.Cross(_Vec2i.AsXmFloat3()).Round().AsXmInt3();
    }

    DirectX::XMINT3 Cross(const DirectX::XMINT3& _xmInt)
    {
      Vec3f fVal = AsXmFloat3();
      return fVal.Cross(DirectX::XMLoadSInt3(&_xmInt)).Round().AsXmInt3();
    }

    float Dot(const DirectX::XMVECTOR& vector)
    {
      return DirectX::XMVectorGetX(DirectX::XMVector2Dot(Load(), vector));
    }

    float Dot(const Vec2i& _Vec2i)
    {
      return DirectX::XMVectorGetX(DirectX::XMVector2Dot(Load(), _Vec2i.Load()));
    }

    float Dot(const DirectX::XMINT2& _xmInt)
    {
      return DirectX::XMVectorGetX(DirectX::XMVector2Dot(Load(), DirectX::XMLoadSInt2(&_xmInt)));
    }

    float Length() const
    {
      return DirectX::XMVectorGetX(DirectX::XMVector2Length(Load()));
    }

    float LengthSq() const
    {
      return DirectX::XMVectorGetX(DirectX::XMVector2LengthSq(Load()));
    }

    std::string ToString() const
    {
      std::string str = "X: " + std::to_string(x) + ", " + "Y: " + std::to_string(y);
      return str;
    }
#pragma endregion

    int& x = m_vec.x;
    int& y = m_vec.y;

  private:
    DirectX::XMINT2 m_vec;
  };

  struct Vec3i
  {
  public:
#pragma region Constructors
    Vec3i(int _x = 0, int _y = 0, int _z = 0)
    {
      m_vec.x = _x;
      m_vec.y = _y;
      m_vec.z = _z;
    }

    Vec3i(const DirectX::XMINT3& _xmInt)
    {
      m_vec = _xmInt;
    }

    Vec3i(const Vec3i& _vec2)
    {
      m_vec = _vec2.m_vec;
    }

#pragma endregion

#pragma region Vector Operators

    Vec3i& operator=(const Vec3i& _Vec3i)
    {
      if (this != &_Vec3i)
      {
        m_vec = _Vec3i.m_vec;
      }

      return *this;
    }

    Vec3i& operator=(const DirectX::XMINT3& _xmInt)
    {
      m_vec = _xmInt;

      return *this;
    }

    Vec3i operator+(const DirectX::XMVECTOR& _xmVec) const
    {
      Vec3i sum;

      sum.Store(DirectX::XMVectorAdd(Load(), _xmVec));

      return sum;
    }

    Vec3i operator-(const DirectX::XMVECTOR& _xmVec) const
    {
      Vec3i sum;

      sum.Store(DirectX::XMVectorSubtract(Load(), _xmVec));

      return sum;
    }

    Vec3i operator*(const DirectX::XMVECTOR& _xmVec)
    {
      Vec3i product;

      product.Store(DirectX::XMVectorMultiply(Load(), _xmVec));

      return product;
    }

    Vec3i operator/(const DirectX::XMVECTOR& _xmVec)
    {
      Vec3i product;

      product.Store(DirectX::XMVectorDivide(Load(), _xmVec));

      return product;
    }

    Vec3i operator+(const Vec3i& _Vec3i) const
    {
      Vec3i sum;

      sum.Store(DirectX::XMVectorAdd(Load(), _Vec3i.Load()));

      return sum;
    }

    Vec3i operator+(const DirectX::XMINT3& _xmInt) const
    {
      Vec3i sum;

      sum.Store(DirectX::XMVectorAdd(Load(), DirectX::XMLoadSInt3(&_xmInt)));

      return sum;
    }

    Vec3i operator-(const Vec3i& _Vec3i) const
    {
      Vec3i sum;

      sum.Store(DirectX::XMVectorSubtract(Load(), _Vec3i.Load()));

      return sum;
    }

    Vec3i operator-(const DirectX::XMINT3& _xmInt) const
    {
      Vec3i sum;

      sum.Store(DirectX::XMVectorSubtract(Load(), DirectX::XMLoadSInt3(&_xmInt)));

      return sum;
    }

    Vec3i operator*(const Vec3i& _Vec3i) const
    {
      Vec3i product;

      product.Store(DirectX::XMVectorMultiply(Load(), _Vec3i.Load()));

      return product;
    }

    Vec3i operator*(const DirectX::XMINT3& _xmInt) const
    {
      Vec3i product;

      product.Store(DirectX::XMVectorMultiply(Load(), DirectX::XMLoadSInt3(&m_vec)));

      return product;
    }

    Vec3i operator/(const Vec3i& _Vec3i) const
    {
      Vec3i product;

      product.Store(DirectX::XMVectorDivide(Load(), _Vec3i.Load()));

      return product;
    }

    Vec3i operator/(const DirectX::XMINT3& _xmInt) const
    {
      Vec3i product;

      product.Store(DirectX::XMVectorDivide(Load(), DirectX::XMLoadSInt3(&m_vec)));

      return product;
    }

    Vec3i operator*(int m)
    {
      Vec3f product;

      product.Store(DirectX::XMVectorScale(Load(), (float)m));

      return product.Round().AsXmInt3();
    }

    Vec3i& operator*=(int m)
    {
      Vec3f product;

      product.Store(DirectX::XMVectorScale(Load(), (float)m));

      *this = product.Round().AsXmInt3();

      return *this;
    }

    Vec3i operator/(int m)
    {
      Vec3f product;

      product.Store(DirectX::XMVectorScale(Load(), 1.0f / (float)m));

      return product.Round().AsXmInt3();
    }

    Vec3i& operator/=(int m)
    {
      Vec3f product;

      product.Store(DirectX::XMVectorScale(Load(), 1.0f / (float)m));

      *this = product.Round().AsXmInt3();

      return *this;
    }

    Vec3i& operator+=(const Vec3i& _Vec3i)
    {
      *this = *this + _Vec3i;

      return *this;
    }

    Vec3i& operator+=(const DirectX::XMINT3& _xmInt)
    {
      *this = *this + _xmInt;

      return *this;
    }

    Vec3i& operator+=(const DirectX::XMVECTOR& _xmVec)
    {
      *this = *this + _xmVec;

      return *this;
    }

    Vec3i& operator-=(const Vec3i& _Vec3i)
    {
      *this = *this - _Vec3i;

      return *this;
    }

    Vec3i& operator-=(const DirectX::XMINT3& _xmInt)
    {
      *this = *this - _xmInt;

      return *this;
    }

    Vec3i& operator-=(const DirectX::XMVECTOR& _xmVec)
    {
      *this = *this - _xmVec;

      return *this;
    }

    Vec3i& operator*=(const Vec3i& _Vec3i)
    {
      *this = *this * _Vec3i;

      return *this;
    }

    Vec3i& operator*=(const DirectX::XMINT3& _xmInt)
    {
      *this = *this * _xmInt;

      return *this;
    }

    Vec3i& operator*=(const DirectX::XMVECTOR& _xmVec)
    {
      *this = *this * _xmVec;

      return *this;
    }

    Vec3i& operator/=(const Vec3i& _Vec3i)
    {
      *this = *this / _Vec3i;

      return *this;
    }

    Vec3i& operator/=(const DirectX::XMINT3& _xmInt)
    {
      *this = *this / _xmInt;

      return *this;
    }

    Vec3i& operator/=(const DirectX::XMVECTOR& _xmVec)
    {
      *this = *this / _xmVec;

      return *this;
    }

    bool operator==(const Vec3i& _Vec3i) const
    {
      return x == _Vec3i.x && y == _Vec3i.y;
    }

    bool operator==(const DirectX::XMINT3& _xmInt) const
    {
      return x == _xmInt.x && y == _xmInt.y;
    }

    bool operator==(const DirectX::XMVECTOR& _xmVec) const
    {
      static float EPSILON = 0.0001f;

      Vec3i val;
      val.Store(_xmVec);

      return *this == val;
    }

#pragma endregion

#pragma region Matrix Operators
    Vec3i operator*(const DirectX::XMMATRIX& _matrix)
    {
      Vec3f val;
      Vec3i iVal;

      val.Store(DirectX::XMVector2Transform(Load(), _matrix));

      iVal = val.Round().AsXmInt3();

      return iVal;
    }

    Vec3i operator*(const DirectX::XMFLOAT4X4& _matrix)
    {
      return *this * DirectX::XMLoadFloat4x4(&_matrix);
    }

    Vec3i operator*(const DirectX::XMFLOAT3X3& _matrix)
    {
      return *this * DirectX::XMLoadFloat3x3(&_matrix);
    }
#pragma endregion

#pragma region Functions

    DirectX::XMVECTOR Load() const
    {
      return DirectX::XMLoadSInt3(&m_vec);
    }

    void Store(const DirectX::XMVECTOR& vector)
    {
      DirectX::XMStoreSInt3(&m_vec, vector);
    }

    DirectX::XMFLOAT2 AsXmFloat2() const
    {
      DirectX::XMFLOAT2 val;
      val.x = (float)x;
      val.y = (float)y;
      return val;
    }

    DirectX::XMFLOAT3 AsXmFloat3() const
    {
      DirectX::XMFLOAT3 val;
      val.x = (float)x;
      val.y = (float)y;
      val.z = 0.0f;

      return val;
    }

    DirectX::XMFLOAT4 AsXmFloat4() const
    {
      DirectX::XMFLOAT4 val;
      val.x = (float)x;
      val.y = (float)y;
      val.z = 0.0f;
      val.w = 0.0f;

      return val;
    }

    DirectX::XMINT2 AsXmInt2() const
    {
      DirectX::XMINT2 val;
      val.x = x;
      val.y = y;

      return val;
    }

    const DirectX::XMINT3& AsXmInt3() const
    {
      return m_vec;
    }

    DirectX::XMINT4 AsXmInt4() const
    {
      DirectX::XMINT4 val;
      val.x = x;
      val.y = y;
      val.z = 0;
      val.w = 0;

      return val;
    }

    Vec3i Abs() const
    {
      return Vec3i(abs(x), abs(y));
    }

    Vec3f Normalize() const
    {
      Vec3f nor;

      nor.Store(DirectX::XMVector3Normalize(Load()));

      return nor;
    }

    Vec3i Cross(const DirectX::XMVECTOR& vector)
    {
      Vec3f fVal = AsXmFloat3();
      return fVal.Cross(vector).Round().AsXmInt3();
    }

    Vec3i Cross(const Vec3i& _Vec3i)
    {
      Vec3f fVal = AsXmFloat3();
      return fVal.Cross(_Vec3i.AsXmFloat3()).Round().AsXmInt3();
    }

    Vec3i Cross(const DirectX::XMINT3& _xmInt)
    {
      Vec3f fVal = AsXmFloat3();
      return fVal.Cross(DirectX::XMLoadSInt3(&_xmInt)).Round().AsXmInt3();
    }

    float Dot(const DirectX::XMVECTOR& vector)
    {
      return DirectX::XMVectorGetX(DirectX::XMVector3Dot(Load(), vector));
    }

    float Dot(const Vec3i& _Vec3i)
    {
      return DirectX::XMVectorGetX(DirectX::XMVector3Dot(Load(), _Vec3i.Load()));
    }

    float Dot(const DirectX::XMINT3& _xmInt)
    {
      return DirectX::XMVectorGetX(DirectX::XMVector3Dot(Load(), DirectX::XMLoadSInt3(&_xmInt)));
    }

    float Length() const
    {
      return DirectX::XMVectorGetX(DirectX::XMVector3Length(Load()));
    }

    float LengthSq() const
    {
      return DirectX::XMVectorGetX(DirectX::XMVector3LengthSq(Load()));
    }

    std::string ToString() const
    {
      std::string str =
          "X: " + std::to_string(x) + ", " + "Y: " + std::to_string(y) + "Z: " + std::to_string(z);
      return str;
    }
#pragma endregion

    int& x = m_vec.x;
    int& y = m_vec.y;
    int& z = m_vec.z;

  private:
    DirectX::XMINT3 m_vec;
  };

  struct Vec4i
  {
  public:
#pragma region Constructors
    Vec4i(int _x = 0, int _y = 0, int _z = 0, int _w = 0)
    {
      m_vec.x = _x;
      m_vec.y = _y;
      m_vec.z = _z;
      m_vec.z = _w;
    }

    Vec4i(const DirectX::XMINT4& _xmInt)
    {
      m_vec = _xmInt;
    }

    Vec4i(const Vec4i& _vec2)
    {
      m_vec = _vec2.m_vec;
    }

#pragma endregion

#pragma region Vector Operators

    Vec4i& operator=(const Vec4i& _Vec4i)
    {
      if (this != &_Vec4i)
      {
        m_vec = _Vec4i.m_vec;
      }

      return *this;
    }

    Vec4i& operator=(const DirectX::XMINT4& _xmInt)
    {
      m_vec = _xmInt;

      return *this;
    }

    Vec4i operator+(const DirectX::XMVECTOR& _xmVec) const
    {
      Vec4i sum;

      sum.Store(DirectX::XMVectorAdd(Load(), _xmVec));

      return sum;
    }

    Vec4i operator-(const DirectX::XMVECTOR& _xmVec) const
    {
      Vec4i sum;

      sum.Store(DirectX::XMVectorSubtract(Load(), _xmVec));

      return sum;
    }

    Vec4i operator*(const DirectX::XMVECTOR& _xmVec)
    {
      Vec4i product;

      product.Store(DirectX::XMVectorMultiply(Load(), _xmVec));

      return product;
    }

    Vec4i operator/(const DirectX::XMVECTOR& _xmVec)
    {
      Vec4i product;

      product.Store(DirectX::XMVectorDivide(Load(), _xmVec));

      return product;
    }

    Vec4i operator+(const Vec4i& _Vec4i) const
    {
      Vec4i sum;

      sum.Store(DirectX::XMVectorAdd(Load(), _Vec4i.Load()));

      return sum;
    }

    Vec4i operator+(const DirectX::XMINT4& _xmInt) const
    {
      Vec4i sum;

      sum.Store(DirectX::XMVectorAdd(Load(), DirectX::XMLoadSInt4(&_xmInt)));

      return sum;
    }

    Vec4i operator-(const Vec4i& _Vec4i) const
    {
      Vec4i sum;

      sum.Store(DirectX::XMVectorSubtract(Load(), _Vec4i.Load()));

      return sum;
    }

    Vec4i operator-(const DirectX::XMINT4& _xmInt) const
    {
      Vec4i sum;

      sum.Store(DirectX::XMVectorSubtract(Load(), DirectX::XMLoadSInt4(&_xmInt)));

      return sum;
    }

    Vec4i operator*(const Vec4i& _Vec4i) const
    {
      Vec4i product;

      product.Store(DirectX::XMVectorMultiply(Load(), _Vec4i.Load()));

      return product;
    }

    Vec4i operator*(const DirectX::XMINT4& _xmInt) const
    {
      Vec4i product;

      product.Store(DirectX::XMVectorMultiply(Load(), DirectX::XMLoadSInt4(&m_vec)));

      return product;
    }

    Vec4i operator/(const Vec4i& _Vec4i) const
    {
      Vec4i product;

      product.Store(DirectX::XMVectorDivide(Load(), _Vec4i.Load()));

      return product;
    }

    Vec4i operator/(const DirectX::XMINT4& _xmInt) const
    {
      Vec4i product;

      product.Store(DirectX::XMVectorDivide(Load(), DirectX::XMLoadSInt4(&m_vec)));

      return product;
    }

    Vec4i operator*(int m)
    {
      Vec4f product;

      product.Store(DirectX::XMVectorScale(Load(), (float)m));

      return product.Round().AsXmInt4();
    }

    Vec4i& operator*=(int m)
    {
      Vec4f product;

      product.Store(DirectX::XMVectorScale(Load(), (float)m));

      *this = product.Round().AsXmInt4();

      return *this;
    }

    Vec4i operator/(int m)
    {
      Vec4f product;

      product.Store(DirectX::XMVectorScale(Load(), 1.0f / (float)m));

      return product.Round().AsXmInt4();
    }

    Vec4i& operator/=(int m)
    {
      Vec4f product;

      product.Store(DirectX::XMVectorScale(Load(), 1.0f / (float)m));

      *this = product.Round().AsXmInt4();

      return *this;
    }

    Vec4i& operator+=(const Vec4i& _Vec4i)
    {
      *this = *this + _Vec4i;

      return *this;
    }

    Vec4i& operator+=(const DirectX::XMINT4& _xmInt)
    {
      *this = *this + _xmInt;

      return *this;
    }

    Vec4i& operator+=(const DirectX::XMVECTOR& _xmVec)
    {
      *this = *this + _xmVec;

      return *this;
    }

    Vec4i& operator-=(const Vec4i& _Vec4i)
    {
      *this = *this - _Vec4i;

      return *this;
    }

    Vec4i& operator-=(const DirectX::XMINT4& _xmInt)
    {
      *this = *this - _xmInt;

      return *this;
    }

    Vec4i& operator-=(const DirectX::XMVECTOR& _xmVec)
    {
      *this = *this - _xmVec;

      return *this;
    }

    Vec4i& operator*=(const Vec4i& _Vec4i)
    {
      *this = *this * _Vec4i;

      return *this;
    }

    Vec4i& operator*=(const DirectX::XMINT4& _xmInt)
    {
      *this = *this * _xmInt;

      return *this;
    }

    Vec4i& operator*=(const DirectX::XMVECTOR& _xmVec)
    {
      *this = *this * _xmVec;

      return *this;
    }

    Vec4i& operator/=(const Vec4i& _Vec4i)
    {
      *this = *this / _Vec4i;

      return *this;
    }

    Vec4i& operator/=(const DirectX::XMINT4& _xmInt)
    {
      *this = *this / _xmInt;

      return *this;
    }

    Vec4i& operator/=(const DirectX::XMVECTOR& _xmVec)
    {
      *this = *this / _xmVec;

      return *this;
    }

    bool operator==(const Vec4i& _Vec4i) const
    {
      return x == _Vec4i.x && y == _Vec4i.y;
    }

    bool operator==(const DirectX::XMINT4& _xmInt) const
    {
      return x == _xmInt.x && y == _xmInt.y;
    }

    bool operator==(const DirectX::XMVECTOR& _xmVec) const
    {
      static float EPSILON = 0.0001f;

      Vec4i val;
      val.Store(_xmVec);

      return *this == val;
    }

#pragma endregion

#pragma region Matrix Operators
    Vec4i operator*(const DirectX::XMMATRIX& _matrix)
    {
      Vec4f val;
      Vec4i iVal;
      val.Store(DirectX::XMVector2Transform(Load(), _matrix));

      iVal = val.Round().AsXmInt4();

      return iVal;
    }

    Vec4i operator*(const DirectX::XMFLOAT4X4& _matrix)
    {
      return *this * DirectX::XMLoadFloat4x4(&_matrix);
    }

    Vec4i operator*(const DirectX::XMFLOAT3X3& _matrix)
    {
      return *this * DirectX::XMLoadFloat3x3(&_matrix);
    }
#pragma endregion

#pragma region Functions

    DirectX::XMVECTOR Load() const
    {
      return DirectX::XMLoadSInt4(&m_vec);
    }

    void Store(const DirectX::XMVECTOR& vector)
    {
      DirectX::XMStoreSInt4(&m_vec, vector);
    }

    DirectX::XMFLOAT2 AsXmFloat2() const
    {
      DirectX::XMFLOAT2 val;
      val.x = (float)x;
      val.y = (float)y;
      return val;
    }

    DirectX::XMFLOAT3 AsXmFloat3() const
    {
      DirectX::XMFLOAT3 val;
      val.x = (float)x;
      val.y = (float)y;
      val.z = 0.0f;

      return val;
    }

    DirectX::XMFLOAT4 AsXmFloat4() const
    {
      DirectX::XMFLOAT4 val;
      val.x = (float)x;
      val.y = (float)y;
      val.z = 0.0f;
      val.w = 0.0f;

      return val;
    }

    DirectX::XMINT2 AsXmInt2() const
    {
      DirectX::XMINT2 val;
      val.x = x;
      val.y = y;

      return val;
    }

    DirectX::XMINT3 AsXmInt3() const
    {
      DirectX::XMINT3 val;
      val.x = x;
      val.y = y;
      val.z = z;

      return val;
    }

    const DirectX::XMINT4& AsXmInt4() const
    {
      return m_vec;
    }

    Vec4i Abs() const
    {
      return Vec4i(abs(x), abs(y));
    }

    Vec4f Normalize(bool ignoreW = false) const
    {
      Vec4f nor;

      if (!ignoreW)
        nor.Store(DirectX::XMVector4Normalize(Load()));
      else
      {
        float _w = (float)w;
        nor.Store(DirectX::XMVector3Normalize(Load()));
        nor.w = _w;
      }

      return nor;
    }

    Vec4i Cross(const DirectX::XMVECTOR& vector)
    {
      Vec3f fVal = AsXmFloat3();
      return fVal.Cross(vector).Round().AsXmInt4();
    }

    Vec4i Cross(const Vec4i& _Vec3i)
    {
      Vec3f fVal = AsXmFloat3();
      return fVal.Cross(_Vec3i.AsXmFloat3()).Round().AsXmInt4();
    }

    Vec4i Cross(const DirectX::XMINT4& _xmInt)
    {
      Vec3f fVal = AsXmFloat3();
      return fVal.Cross(DirectX::XMLoadSInt4(&_xmInt)).Round().AsXmInt4();
    }

    float Dot(const DirectX::XMVECTOR& vector)
    {
      return DirectX::XMVectorGetX(DirectX::XMVector3Dot(Load(), vector));
    }

    float Dot(const Vec4i& _Vec4i)
    {
      return DirectX::XMVectorGetX(DirectX::XMVector3Dot(Load(), _Vec4i.Load()));
    }

    float Dot(const DirectX::XMINT4& _xmInt)
    {
      return DirectX::XMVectorGetX(DirectX::XMVector3Dot(Load(), DirectX::XMLoadSInt4(&_xmInt)));
    }

    float Length() const
    {
      return DirectX::XMVectorGetX(DirectX::XMVector4Length(Load()));
    }

    float LengthSq() const
    {
      return DirectX::XMVectorGetX(DirectX::XMVector4LengthSq(Load()));
    }

    std::string ToString() const
    {
      std::string str = "X: " + std::to_string(x) + ", " + "Y: " + std::to_string(y) +
                        "Z: " + std::to_string(z) + "W: " + std::to_string(w);
      return str;
    }
#pragma endregion
    int& x = m_vec.x;
    int& y = m_vec.y;
    int& z = m_vec.z;
    int& w = m_vec.w;

  private:
    DirectX::XMINT4 m_vec;
  };

} // namespace DM

namespace std
{
  template <>
  struct hash<DM::Vec3f>
  {
    size_t operator()(const DM::Vec3f& p) const
    {
      size_t lol =
          std::hash<float>()(p.x) ^ std::hash<float>()(p.y) ^ std::hash<float>()(p.z);
      return lol;
    }
  };
} // namespace std