#pragma once
#include <DirectXMath.h>
#include "../../utility/Typedef.h"
#define MAX_LIGHTS 256
enum class LightType : uint
{
  PointLight = 0,
  DirectionalLight,
  NrOfLightTypes
};

struct Light
{
  LightType          type;
  float              dropOff;
  float              pow;
  float              radius;
  float              intensity;
  float              pad[3];
  union
  {
    DirectX::XMFLOAT4A direction;
    DirectX::XMFLOAT4A position;
  };
  DirectX::XMFLOAT4A color;
};