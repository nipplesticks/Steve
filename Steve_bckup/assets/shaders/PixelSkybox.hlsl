#include "DeferredOutput.hlsli"
SamplerState aSampler : register(s0);
Texture2D<float4> aTexture : register(t0);

struct Vertex
{
  float4 pos : SV_POSITION;
  float4 nor : NORMAL;
  float4 uv : TEXCOORD;
};

DeferredOutput main(Vertex vertex)
{
  DeferredOutput output;
  GetDefaultDeferredOutput(output);
  float3 color = aTexture.Sample(aSampler, vertex.uv.xy).rgb;
  output.color = saturate(float4(color, 1.0f));
  return output;
}