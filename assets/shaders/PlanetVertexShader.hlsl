cbuffer cbv0 : register(b0)
{
  float4x4 view;
  float4x4 proj;
};

cbuffer cbv1 : register(b1)
{
  float4x4 worldMat;
}

cbuffer cbv2 : register(b3)
{
  float4 waterLevel;
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
  float h = length(vertex.pos.xyz);
  if (h <= waterLevel.x)
  {
    vertex.pos = float4(normalize(vertex.pos.xyz) * waterLevel.x, 1.0f);
    vertex.nor = float4(normalize(vertex.pos.xyz), 0.0f);
  }
  
  vertex.pos = mul(vertex.pos, transpose(worldMat));
  vertex.nor = normalize(mul(vertex.nor, transpose(worldMat)));
  vertex.pos = mul(vertex.pos, transpose(mul(proj, view)));

  return vertex;
}