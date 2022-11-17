#include "Datatypes.hlsli"
#include "../PixelOutput.hlsli"
SamplerState      aSampler : register(s0);
Texture2D<float4> diffuseMap : register(t0);
Texture2D<float4> bumpMap : register(t1);

PixelOutput main(VS_OUT input)
{
  PixelOutput output;
  output.position = input.worldPosition;

  float3x3 TBN = {input.tangent.xyz, input.normal.xyz, input.bitangent.xyz};
  output.normal =
      float4(normalize(mul(bumpMap.Sample(aSampler, input.uv).rgb * 2.0f - 1.0f, TBN)), 0.0f);
  output.color = diffuseMap.Sample(aSampler, input.uv);
  return output;
}