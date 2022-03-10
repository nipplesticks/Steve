SamplerState aSampler : register(s0);
Texture2D<float4> worldPositionTexture : register(t0);
Texture2D<float4> normalTexture : register(t1);
Texture2D<float4> colorTexture : register(t2);
Texture2D<uint> pickableIdTexture : register(t3);

struct VS_OUT
{
  float4 position : SV_POSITION;
  float2 uv : TEXCOORD;
};

float4 main(VS_OUT vIn) : SV_TARGET
{
  float4 finalColor = colorTexture.Sample(aSampler, vIn.uv);
  
  return finalColor;
}