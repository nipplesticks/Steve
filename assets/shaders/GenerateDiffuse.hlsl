#include "PerlinNoise_cs.hlsli"
RWTexture2D<float> heightMap : register(u0);
RWTexture2D<float4> diffuseTexture : register(u1);

cbuffer Generation : register(b0)
{
  float frequency;
  float exponent;
  float fudgeFactor;
  uint iterations;
  float waterLevel;
  float4 textureSize;
  int permutation[256];
};

void SetPixel(uint2 texCoord, float elevation, float moisture)
{
  float3 color;
  //if (elevation < (waterLevel.x))
  //  color = float3(18, 17, 84) / 255.0f;
  if (elevation < (waterLevel.x)
    + 0.02)
    color = float3(179, 162, 133) / 255.0f;
  else if (elevation > 0.8)
  {
    if (moisture < 0.1)
      color = float3(53, 31, 25) / 255.0f;
    if (moisture < 0.2)
      color = float3(142, 106, 80) / 255.0f;
    if (moisture < 0.5)
      color = float3(213, 90, 59) / 255.0f;
    color = float3(255, 255, 255) / 255.0f;
  }
  else if (elevation > 0.6)
  {
    if (moisture < 0.33)
      color = float3(213, 129, 82) / 255.0f;
    else if (moisture < 0.66)
      color = float3(166, 165, 121) / 255.0f;
    else
      color = float3(18, 47, 16) / 255.0f;
  }
  else if (elevation > 0.3)
  {
    if (moisture < 0.16)
      color = float3(213, 129, 82) / 255.0f;
    else if (moisture < 0.50)
      color = float3(82, 90, 14) / 255.0f;
    else if (moisture < 0.83)
      color = float3(120, 173, 4) / 255.0f;
    else
      color = float3(64, 80, 40) / 255.0f;
  }
  else
  {
    if (moisture < 0.16)
      color = float3(208, 160, 113) / 255.0f;
    else if (moisture < 0.33)
      color = float3(82, 90, 14) / 255.0f;
    else if (moisture < 0.66)
      color = float3(75, 148, 94) / 255.0f;
    else
      color = float3(72, 120, 80) / 255.0f;
  }
  diffuseTexture[texCoord] = float4(color, 1.0f);
}

[numthreads(32, 32, 1)]
void main(uint3 threadID : SV_DispatchThreadID)
{
  const float PI = 3.14159265359f;
  
  int x = threadID.x;
  int y = threadID.y;
  float _x = (float) x / (float) textureSize.x;
  float _y = (float) y / (float) textureSize.y;
  float yCoord = sin(_y * PI - PI / 2);
  float xCoord = cos(_x * 2.0 * PI) * cos(_y * PI - PI / 2.0);
  float zCoord = sin(_x * 2.0 * PI) * cos(_y * PI - PI / 2.0);
  
  float f = frequency;
  float m = 0.0f;
  float div = 0.0f;
  
  for (uint i = 0; i < iterations; i++)
  {
    float it = frequency / f;
    m += it * PerlineNoise(xCoord * f, yCoord * f, zCoord * f, permutation);
    div += it;
    m *= 2.0f;
  }
  if (div > 0.0f)
    m = m / div;
  m = pow(abs(m * fudgeFactor), exponent);
  float e = heightMap[uint2(threadID.xy)];
  SetPixel(threadID.xy, e, m);
}