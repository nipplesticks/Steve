RWTexture2D<float> heightMap : register(u0);
RWTexture2D<float4> bumpMap : register(u1);

float3 GetNormal(float3 a, float3 b, float3 c)
{
  float3 e0 = normalize(b - a);
  float3 e1 = normalize(c - a);
  float3 n = normalize(cross(e1, e0));
  return n;
}

void CalcNormalTry1(int _x, int _z, uint width, uint height)
{
  float3 points[9];
  
  int idX = 0;
  int idY = 0;
  
  for (int zz = _z - 1; zz <= _z + 1; zz++)
  {
    int z = zz < 0 ? height - 1 : zz;
    z = z >= height ? 0 : z;
    for (int xx = _x - 1; xx <= _x + 1; xx++)
    {
      int x = xx < 0 ? width - 1 : xx;
      x = x >= width ? 0 : x;
      points[idX + idY * 3].x =
        (float) x / (float) width;
      points[idX + idY * 3].y =
        heightMap[uint2(x, z)];
      points[idX + idY * 3].z = (float) z / (float) height;
      idX++;
    }
    idY++;
  }
  float3 target = points[4];
  float3 normals = float3(0, 0, 0);
  normals += GetNormal(target, points[0], points[1]);
  normals += GetNormal(target, points[1], points[2]);
  normals += GetNormal(target, points[3], points[0]);
  normals += GetNormal(target, points[2], points[5]);
  normals += GetNormal(target, points[6], points[3]);
  normals += GetNormal(target, points[7], points[6]);
  normals += GetNormal(target, points[8], points[7]);
  normals += GetNormal(target, points[5], points[8]);
  normals = normalize(normals / 8);
  bumpMap[uint2(_x, _z)] = float4(normals, 0.0f);
}

[numthreads(1, 1, 1)]
void main(uint3 dispatchThreadId : SV_DispatchThreadID)
{
  int x = dispatchThreadId.x;
  int y = dispatchThreadId.y;
  uint width, height;
  heightMap.GetDimensions(width, height);
  
  //CalcNormalTry1(x, y, width, height);
  float3 a = float3((float) x / width, heightMap[uint2(x, y)], (float) y / height);
  float3 b = float3((float) (x + 1) / width, heightMap[uint2(x + 1, y)], (float) y / height);
  float3 c = float3((float) x / width, heightMap[uint2(x, y + 1)], (float) (y + 1) / height);
  bumpMap[uint2(x, y)] = float4(GetNormal(a, b, c), 0.0f);
}