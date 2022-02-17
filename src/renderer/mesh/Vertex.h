#pragma once
#include <DirectXMath.h>

enum class VertexType
{
  VertexBasic = 0,
  VertexTangent,
  NumberOfVertexTypes
};

struct TangentBitangent
{
  DirectX::XMFLOAT4A tangent;
  DirectX::XMFLOAT4A bitangent;
};

struct Vertex_Basic
{
  DirectX::XMFLOAT4A position;
  DirectX::XMFLOAT4A normal;
  DirectX::XMFLOAT2A uv;
};

struct Vertex_With_Tangent
{
  Vertex_Basic vertexBasic;
  TangentBitangent tangentBitangent;
};

struct Vertex
{
  union
  {
    Vertex_Basic vertexBasic;
    Vertex_With_Tangent vertexTangent;
  };
};