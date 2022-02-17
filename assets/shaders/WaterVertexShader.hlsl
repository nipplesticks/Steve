cbuffer cbv0 : register(b0)
{
  float4x4 view;
  float4x4 proj;
};

cbuffer cbv1 : register(b1)
{
  float4x4 worldMat;
}

cbuffer cbv2 : register(b2)
{
  float uvOffset;
}

struct VS_IN
{
  float4 pos : SV_POSITION;
  float4 nor : NORMAL;
  float4 uv : TEXCOORD;
};

struct VS_OUT
{
  float4 worldPos : WORLD_POS;
  float4 pos : SV_POSITION;
  float4 uv : TEXCOORD;
  float4 tangent : TANGENT;
  float4 bitangent : BITANGENT;
  float4 nor : NORMAL;
};

struct TangentBitangent
{
  float4 tangent;
  float4 bitangent;
};

StructuredBuffer<TangentBitangent> tangents : register(t0);

VS_OUT main(VS_IN vIn, uint pid : SV_VertexID)
{
  VS_OUT vOut;
  vIn.pos = mul(vIn.pos, transpose(worldMat));
  vOut.worldPos = vIn.pos;
  
  vIn.nor = (normalize(mul(vIn.nor, transpose(worldMat))));
  vIn.nor.w = 0.0f;
  
  vIn.pos = mul(vIn.pos, transpose(mul(proj, view)));
  
  vIn.uv.x += uvOffset.x;
  vIn.uv.y += uvOffset.x;
  
  vOut.pos = vIn.pos;
  vOut.uv = vIn.uv;
  vOut.nor = vIn.nor;
  vOut.tangent = normalize(mul(tangents[pid / 3].tangent, transpose(worldMat)));
  vOut.bitangent = normalize(mul(tangents[pid / 3].bitangent, transpose(worldMat)));
  return vOut;
}