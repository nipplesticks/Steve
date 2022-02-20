#include "LightCalculations.hlsli"
SamplerState aSampler : register(s0);
Texture2D<float4> diffuseTexture : register(t2);
StructuredBuffer<Light> lightBuffer : register(t3);

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

cbuffer cbv2 : register(b2)
{
  float4x4 WaterWorldMat;
  float4x4 WaterWorldMatInverse;
  uint WaterNumberOfLights;
}

struct Vertex
{
  float4 worldPos : WORLD_POS;
  float4 pos : SV_POSITION;
  float4 uv : TEXCOORD;
  float4 nor : NORMAL;
};

float4 main(Vertex vertex)
    : SV_TARGET
{
  // X: 0.917060, Y: -0.398749, Z: 0.000000
  float3 lightDir = normalize(float3(-0.917060, -0.398749, 0.000000));
  float3 color = diffuseTexture.Sample(aSampler, vertex.uv.xy).rgb;
  float3 ambient = color * 0.2f;
  float3 finalColor = float3(0, 0, 0);
  float4 specularHighlight = float4(0, 0, 0, 0);
  for (uint i = 0; i < numberOfLights; i++)
  {
    finalColor += LightCalculation(lightBuffer[i], cameraPosition, vertex.worldPos, float4(color, 1.0f), vertex.nor, 0.1f, 32.0f, specularHighlight).rgb;
  }
  //return float4(color + finalColor.xyz * 0, 1.0f);
  //float4 c = float4(finalColor + ambient + specularHighlight.rgb, 1.0f);
  
  return saturate(float4(finalColor + ambient + specularHighlight.rgb, 1.0f));
  //return (float4(vertex.nor.xyz + c.xyz * 0.0f, 1.0f));
  //return (float4(float3(1,1,1) + finalColor.xyz * 0.0f, 1.0f));
  //return float4(color, 1.0f);
}