cbuffer cbv0 : register(b0)
{
  float4x4 view;
  float4x4 proj;
  float4 cameraPosition;
};

cbuffer cbv1 : register(b1)
{
  float4x4 worldMat;
  float4x4 worldInverse;
  uint pickableId;
  uint numberOfLights;
}

struct VS_IN
{
  float4 pos : SV_POSITION;
  float4 worldPos : WORLDPOS;
  float4 nor : NORMAL;
  float4 uv : TEXCOORD;
};

VS_IN main(VS_IN vIn)
{
  vIn.worldPos = mul(vIn.pos, transpose(worldMat));
  vIn.pos = mul(vIn.worldPos, transpose(mul(proj, view)));
  
  return vIn;
}