#include "PerlinNoise_cs.hlsli"

RWTexture2D<float4> heightMap : register(u0);

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
  
  float f = genType.height.frequency;
  float e = 0.0f;
  float div = 0.0f;
  
  for (uint i = 0; i < genType.height.iterations; i++)
  {
    float it = genType.height.frequency / f;
    e += it * PerlineNoise(xCoord * f, yCoord * f, zCoord * f, permutation);
    div += it;
    f *= 2.0f;
  }
  if (div > 0.0f)
    e = e / div;
  e = pow(abs(e * genType.height.fudge), genType.height.exp);
  heightMap[uint2(threadID.xy)] = float4(e, e, e, 1.0f);
}