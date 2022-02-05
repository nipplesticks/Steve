#include "PerlinNoise_cs.hlsli"
RWTexture2D<float> heightMap : register(u0);

cbuffer Generation : register(b0)
{
  float frequency;
  float exponent;
  float fudgeFactor;
  uint iterations;
  float4 textureSize;
};

cbuffer Permutation : register(b1)
{
  int permutation[256];
};


[numthreads(32, 32, 1)]
void main(
    uint3 dispatchThreadId : SV_DispatchThreadID)
{
  const float PI = 3.141592654f;
  
  int x = dispatchThreadId.x;
  int y = dispatchThreadId.y;
  float _x = (float) x / textureSize.x;
  float _y = (float) y / textureSize.y;
  float yCoord = sin(_y * PI - PI / 2);
  float xCoord = cos(_x * 2.0 * PI) * cos(_y * PI - PI / 2.0);
  float zCoord = sin(_x * 2.0 * PI) * cos(_y * PI - PI / 2.0);
  
  float f = frequency;
  float e = 0.0f;
  float div = 0.0f;
  
  for (uint i = 0; i < iterations; i++)
  {
    float it = frequency / f;
    e += it * PerlineNoise(xCoord * f, yCoord * f, zCoord * f, permutation);
    div += it;
    f *= 2.0f;
  }
  if (div > 0.0f)
    e = e / div;
  e = pow(abs(e * fudgeFactor), exponent);
  heightMap[dispatchThreadId.xy] = e;
}