#include "PerlinNoise_cs.hlsli"
RWTexture2D<float4> heightMap : register(u0);
RWTexture2D<float4> diffuseTexture : register(u1);

struct GenerationOptions
{
  float frequency;
  float exp;
  float fudge;
  uint iterations;
};

struct GenerationType
{
  GenerationOptions height;
  GenerationOptions moisture;
  float waterLevel;
  uint texWidth;
  uint texHeight;
  uint seed;
};

cbuffer generationSettings : register(b0)
{
  int permutation[256];
  GenerationType genType;
};

void SetPixel(uint2 texCoord, float elevation, float moisture)
{
  float4 color;
  
  if (elevation < genType.waterLevel)
    color = float4(18, 17, 84, 255) / 255.0f;
  else if (elevation < genType.waterLevel + 0.02)
    color = float4(179, 162, 133, 255) / 255.0f;
  else if (elevation > 0.8)
  {
    if (moisture < 0.1)
      color = float4(53, 31, 25, 255) / 255.0f;
    if (moisture < 0.2)
      color = float4(142, 106, 80, 255) / 255.0f;
    if (moisture < 0.5)
      color = float4(213, 90, 59, 255) / 255.0f;
    color = float4(255, 255, 255, 255) / 255.0f;
  }
  else if (elevation > 0.6)
  {
    if (moisture < 0.33)
      color = float4(213, 129, 82, 255) / 255.0f;
    else if (moisture < 0.66)
      color = float4(166, 165, 121, 255) / 255.0f;
    else
      color = float4(18, 47, 16, 255) / 255.0f;
  }
  else if (elevation > 0.3)
  {
    if (moisture < 0.16)
      color = float4(213, 129, 82, 255) / 255.0f;
    else if (moisture < 0.50)
      color = float4(82, 90, 14, 255) / 255.0f;
    else if (moisture < 0.83)
      color = float4(120, 173, 4, 255) / 255.0f;
    else
      color = float4(64, 80, 40, 255) / 255.0f;
  }
  else
  {
    if (moisture < 0.16)
      color = float4(208, 160, 113, 255) / 255.0f;
    else if (moisture < 0.33)
      color = float4(82, 90, 14, 255) / 255.0f;
    else if (moisture < 0.66)
      color = float4(75, 148, 94, 255) / 255.0f;
    else
      color = float4(72, 120, 80, 255) / 255.0f;
  }
  diffuseTexture[texCoord] = color;
}

[numthreads(1, 1, 1)]
void main(uint3 threadID : SV_DispatchThreadID)
{
  const float PI = 3.14159265359f;
  
  int x = threadID.x;
  int y = threadID.y;
  float _x = (float) x / (float) genType.texWidth;
  float _y = (float) y / (float) genType.texHeight;
  float yCoord = sin(_y * PI - PI / 2);
  float xCoord = cos(_x * 2.0 * PI) * cos(_y * PI - PI / 2.0);
  float zCoord = sin(_x * 2.0 * PI) * cos(_y * PI - PI / 2.0);
  
  float f = genType.moisture.frequency;
  float m = 0.0f;
  float div = 0.0f;
  
  for (uint i = 0; i < genType.moisture.iterations; i++)
  {
    float it = genType.moisture.frequency / f;
    m += it * PerlineNoise(xCoord * f, yCoord * f, zCoord * f, permutation);
    div += it;
    m *= 2.0f;
  }
  if (div > 0.0f)
    m = m / div;
  m = pow(abs(m * genType.moisture.fudge), genType.moisture.exp);
  float e = heightMap[uint2(threadID.xy)].r;
  SetPixel(uint2(threadID.xy), e, m);
}