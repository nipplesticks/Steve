#pragma once
#include <DirectXMath.h>
#include "../../utility/Typedef.h"

struct alignas(256) LightDirectional
{
  uint               type;
  union
  {
    DirectX::XMFLOAT4A direction;
    DirectX::XMFLOAT4A position;
  };
  DirectX::XMFLOAT4A color;
};