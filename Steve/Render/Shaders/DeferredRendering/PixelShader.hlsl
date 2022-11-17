#include "Datatypes.hlsli"
#include "LightCalculations.hlsli"
#include "../Buffers.hlsli"

SamplerState      aSampler : register(s0);
Texture2D<float4> worldPositionTexture : register(t0);
Texture2D<float4> normalTexture : register(t1);
Texture2D<float4> colorTexture : register(t2);

cbuffer cbv0 : register(b0)
{
  CameraBuffer cameraBuffer;
};

float4 main(VS_IN_OUT input)
    : SV_TARGET
{
  Light light;
  light.type                = DIRECTIONAL_LIGHT;
  light.dropOff             = 1;
  light.pow                 = 1;
  light.radius              = 1;
  light.intensity           = 1;
  light.positionOrDirection = normalize(float4(-10, 10, 10, 0));
  light.color               = float4(1, 1, 1, 1);
  float4 specularHighlight  = float4(0, 0, 0, 0);

  float4 diffuse = colorTexture.Sample(aSampler, input.uv);
  float4 ambient = diffuse * 0.3f;
  float4 color = LightCalculation(light,
                                  cameraBuffer.position,
                                  worldPositionTexture.Sample(aSampler, input.uv),
                                  diffuse,
                                  normalTexture.Sample(aSampler, input.uv),
                                  0.1f,
                                  1.0f,
                                  specularHighlight);

  return saturate(ambient + color + specularHighlight);
  return saturate(diffuse);
}