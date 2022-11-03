struct VS_IN
{
  float4 position : SV_POSITION;
  float4 normal : NORMAL;
  float2 uv : TEXCOORD;
  float4 tangent : TANGENT;
  float4 bitangent : BITANGENT;
};

struct VS_OUT
{
  float4 worldPosition : WORLDPOS;
  float4 position : SV_POSITION;
  float4 normal : NORMAL;
  float2 uv : TEXCOORD;
  float4 tangent : TANGENT;
  float4 bitangent : BITANGENT;
};