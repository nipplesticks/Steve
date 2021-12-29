SamplerState      aSampler : register(s0);
Texture2D<float4> aTexture : register(t0);

struct Vertex
{
  float4 pos : SV_POSITION;
  float4 col : COLOR;
  float4 nor : NORMAL;
  float4 uv  : TEXCOORD;
};

float4 main(Vertex vertex)
    : SV_TARGET
{
  float3 lightDir = normalize(float3(0.0f, 0.0f, -1.0f));
  float3 color = aTexture.Sample(aSampler, vertex.uv.xy).rgb * vertex.col.rgb;
  float4 pos      = vertex.pos;
  float3 ambient  = float3(0.05f, 0.05f, 0.05f);

  float3 finalColor = max(dot(normalize(vertex.nor.xyz), -lightDir), ambient) * color;

  //return min(float4(finalColor, 1.0f), 1.0f);
  return float4(color, 1.0f);
  //return float4(pos.x, pos.y, pos.z, 1.0f);
  //return float4(vertex.uv.x, vertex.uv.y, 1.0f, 1.0f);
}