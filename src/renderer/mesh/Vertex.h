#pragma once
#include <DirectXMath.h>

struct Vertex
{
  DirectX::XMFLOAT4A position;
  DirectX::XMFLOAT4A color;
  DirectX::XMFLOAT4A normal;
  DirectX::XMFLOAT4A tangent;
  DirectX::XMFLOAT4A bitangent;
  DirectX::XMFLOAT4A uv;
};