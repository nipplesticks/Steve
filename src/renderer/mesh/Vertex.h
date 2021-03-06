#pragma once
#include <DirectXMath.h>

struct alignas(256) DefaultConstantBufferContent
{
  DirectX::XMFLOAT4X4A worldMatrix;
  DirectX::XMFLOAT4X4A worldMatrixInverse;
  unsigned int         pickableId = UINT_MAX;
  unsigned int         numberOfLights = 0;
};

enum class VertexType
{
  VertexBasic = 0,
  VertexWithTangent,
  NumberOfVertexTypes
};

struct TangentBitangent
{
  DirectX::XMFLOAT4A tangent;
  DirectX::XMFLOAT4A bitangent;
};

struct Vertex_Basic_No_UV
{
  DirectX::XMFLOAT4A position;
  DirectX::XMFLOAT4A normal;
};

struct Vertex_Basic
{
  DirectX::XMFLOAT4A position;
  DirectX::XMFLOAT4A normal;
  DirectX::XMFLOAT2A uv;
};

struct Vertex_With_Tangent
{
  Vertex_Basic     vertexBasic;
  TangentBitangent tangentBitangent;
};

struct Vertex
{
  union
  {
    Vertex_Basic        vertexBasic;
    Vertex_With_Tangent vertexTangent;
  };
};