cbuffer cbv0 : register(b0)
{
  float4x4 view;
  float4x4 proj;
};

cbuffer cbv1 : register(b1)
{
  float4x4 worldMat;
}

struct Vertex
{
  float4 pos : SV_POSITION;
  float4 col : COLOR;
  float4 nor : NORMAL;
  float4 uv : TEXCOORD;
};

Vertex main(Vertex vertex)
{
  vertex.pos = mul(vertex.pos, transpose(worldMat));
  vertex.nor = normalize(mul(vertex.nor, transpose(worldMat)));
  vertex.pos = mul(vertex.pos, transpose(mul(proj, view)));

  return vertex;
}