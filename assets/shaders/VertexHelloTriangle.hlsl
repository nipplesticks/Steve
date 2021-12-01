cbuffer cbv0 : register(b0)
{
  float4x4 viewProj;
};

struct Vertex
{
  float4 pos : SV_POSITION;
  float4 col : COLOR;
  float4 uv : TEXCOORD;
};

Vertex main(Vertex vertex)
{
  vertex.pos = mul(vertex.pos, transpose(viewProj));

  return vertex;
}