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
  float3 lightDir = normalize(float3(1.0f, -1.0f, 0.0f));
  float3 color    = float3(0.5f, 0.5f, 0.5f);
  color           = color * (1.0f - dot(vertex.nor.xyz, lightDir));

  return float4(color, 1.0f);
}