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

struct VS_IN
{
  float4 pos : SV_POSITION;
  float4 col : COLOR;
  float4 nor : NORMAL;
  float4 tangent : TANGENT;
  float4 bitangent : BITANGENT;
  float4 uv : TEXCOORD;
};

struct VS_OUT
{
  float4 worldPos : WORLD_POS;
  float4 pos : SV_POSITION;
  float4 col : COLOR;
  float4 uv : TEXCOORD;
  float4 tangent : TANGENT;
  float4 bitangent : BITANGENT;
  float4 nor : NORMAL;
};

VS_OUT main(VS_IN vIn)
{
  VS_OUT vOut;
  vIn.pos = mul(vIn.pos + vIn.nor * waterLevel.x, transpose(worldMat));
  vOut.worldPos = vIn.pos;
  
  vIn.nor = (normalize(mul(vIn.nor, transpose(worldMat))));
  vIn.nor.w = 0.0f;
  
  vIn.pos = mul(vIn.pos, transpose(mul(proj, view)));
  
  vOut.pos = vIn.pos;
  vOut.col = vIn.col;
  vOut.uv = vIn.uv;
  vOut.nor = vIn.nor;
  vOut.bitangent = mul(vIn.bitangent, transpose(worldMat));
  vOut.tangent = mul(vIn.tangent, transpose(worldMat));
  return vOut;
}