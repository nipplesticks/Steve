SamplerState aSampler : register(s0);
Texture2D<float4> aTexture : register(t0);

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
  float4 uv : TEXCOORD;
};

struct VS_OUT
{
  float4 worldPos : WORLD_POS;
  float4 pos : SV_POSITION;
  float4 col : COLOR;
  float4 uv : TEXCOORD;
  float4 nor : NORMAL;
};

VS_OUT main(VS_IN vIn)
{
  VS_OUT vOut;
  
  float r = aTexture.SampleLevel(aSampler, vIn.uv.xy, 0).r;
  vIn.pos = float4(vIn.pos.xyz + vIn.nor.xyz * r, 1);
  float h = length(vIn.pos.xyz);
  if (h <= waterLevel.x)
  {
    vIn.pos = float4(normalize(vIn.pos.xyz) * waterLevel.x, 1.0f);
    vIn.nor = float4(normalize(vIn.pos.xyz), 0.0f);
  }
  
  vIn.pos = mul(vIn.pos, transpose(worldMat));
  vOut.worldPos = vIn.pos;
  
  vIn.nor = normalize(mul(vIn.nor, transpose(worldMat)));
  vIn.pos = mul(vIn.pos, transpose(mul(proj, view)));
  
  vOut.pos = vIn.pos;
  vOut.col = vIn.col;
  vOut.uv = vIn.uv;
  vOut.nor = vIn.nor;
  
  return vOut;
}