SamplerState aSampler : register(s0);
Texture2D<float> heightMap : register(t0);
Texture2D<float4> bumpMap : register(t1);

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
  uint numberOfLights;
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
  float4 nor : NORMAL;
};

VS_OUT main(VS_IN vIn)
{
  VS_OUT vOut;
  
  float r = heightMap.SampleLevel(aSampler, vIn.uv.xy, 0).r;
  float3 normal = bumpMap.SampleLevel(aSampler, vIn.uv.xy, 0).rgb;
  vIn.pos = float4(vIn.pos.xyz + vIn.nor.xyz * r, 1);
  vIn.pos = mul(vIn.pos, transpose(worldMat));
  vOut.worldPos = vIn.pos;
  vIn.nor = (normalize(mul(float4(normal, 0.0f), transpose(worldMat))));
  vIn.nor.w = 0.0f;
  vIn.pos = mul(vIn.pos, transpose(mul(proj, view)));
  vOut.pos = vIn.pos;
  vOut.uv = vIn.uv;
  vOut.nor = vIn.nor;
  
  return vOut;
}