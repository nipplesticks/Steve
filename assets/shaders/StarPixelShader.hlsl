#include "DeferredOutput.hlsli"

struct VS_OUT
{
  float4 pos : SV_POSITION;
  float4 worldPos : WORLDPOS;
  float4 nor : NORMAL;
  float4 uv : TEXCOORD;
};

DeferredOutput main(VS_OUT vIn)
{
  DeferredOutput output;
  output.position = vIn.worldPos;
  output.normal = vIn.nor;
  output.color = float4(0.976f, 0.843f, 0.109f, 1.0f);
  output.pickableId = 0;
  return output;
}