#include "LightCalculations.hlsli"
#include "DeferredOutput.hlsli"

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
SamplerState aSampler : register(s0);
Texture2D<float4> bumpMap : register(t1);
StructuredBuffer<Light> lightBuffer : register(t2);

struct VS_OUT
{
  float4 worldPos : WORLD_POS;
  float4 pos : SV_POSITION;
  float4 uv : TEXCOORD;
  float4 tangent : TANGENT;
  float4 bitangent : BITANGENT;
  float4 nor : NORMAL;
};

DeferredOutput main(VS_OUT vIn)
{
  DeferredOutput output;
  float3 lightDir = normalize(float3(-0.917060, -0.398749, 0.000000));
  float3 T = normalize(vIn.tangent.xyz);
  float3 N = normalize(vIn.nor.xyz);
  float3 B = normalize(vIn.bitangent.xyz);
  float3x3 TBN = { T, B, N };
  
  float3 aNormal = bumpMap.Sample(aSampler, float2(-vIn.uv.x, vIn.uv.y)).rgb;
  aNormal = aNormal * 2.0f - 1.0f;
  aNormal = normalize(mul(aNormal, TBN));
  
  float3 color = float3(0, 0.1607f, 0.2275f);
  float3 ambient = color * 0.5f;
  //float3 finalColor = max(dot(aNormal, -lightDir), ambient) * color;
  
  float3 finalColor = float3(0, 0, 0);
  
  float4 specularHighlight = float4(0, 0, 0, 0);
  
  for (uint i = 0; i < numberOfLights; i++)
  {
    finalColor += LightCalculation(lightBuffer[i], cameraPosition, vIn.worldPos, float4(color, 1.0f), float4(aNormal, 0.0f), 0.6f, 64.0f, specularHighlight).rgb;
  }
  
  output.position = vIn.worldPos;
  output.normal = float4(aNormal, 0.0f);
  output.color = float4(finalColor + ambient + specularHighlight.rgb, 0.9f);
  output.pickableId = 0;
  //return saturate(float4(finalColor + ambient + specularHighlight.rgb, 0.9f));
  //return float4(aNormal, 1.0f);
  return output;
}