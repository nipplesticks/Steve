cbuffer cbv0 : register(b0)
{
  float4x4 view;
  float4x4 proj;
};

struct Vertex
{
  float4 pos : SV_POSITION;
  float4 col : COLOR;
  float4 nor : NORMAL;
  float4 tangent : TANGENT;
  float4 bitangent : BITANGENT;
  float4 uv : TEXCOORD;
};

Vertex main(Vertex vertex)
{
  float4x4 viewWithoutTranslation = view;
  viewWithoutTranslation[0][3] = viewWithoutTranslation[1][3] = viewWithoutTranslation[2][3] = 0.0f;
  vertex.pos = mul(vertex.pos, transpose(mul(proj, viewWithoutTranslation)));
  vertex.pos.z = 1.0f;

  return vertex;
}