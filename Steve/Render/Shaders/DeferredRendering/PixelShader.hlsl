#include "Datatypes.hlsli"

SamplerState      aSampler : register(s0);
Texture2D<float4> worldPositionTexture : register(t0);
Texture2D<float4> normalTexture : register(t1);
Texture2D<float4> colorTexture : register(t2);

float4 main(VS_IN_OUT input)
    : SV_TARGET
{
  //return colorTexture.Sample(aSampler, input.uv);
  return float4(input.position);
}