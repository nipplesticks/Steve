SamplerState aSampler : register(s0);
Texture2D<float4> aTexture : register(t0);

struct Vertex
{
  float4 pos : SV_POSITION;
  float4 col : COLOR;
  float4 nor : NORMAL;
  float4 uv : TEXCOORD;
};

float4 main(Vertex vertex)
    : SV_TARGET
{
  float3 color = aTexture.Sample(aSampler, vertex.uv.xy).rgb;
  return saturate(float4(color, 1.0f));
}