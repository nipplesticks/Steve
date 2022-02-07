RWTexture2D<float> heightMap : register(u0);
RWTexture2D<float4> bumpMap : register(u1);
static const float PI = 3.141592654f;

float3 GetModelPosisitonFromThreadID(int2 threadID, int2 offset, int2 size, out float2 uv)
{
  float3 modelPos;
  uv = (float2)(threadID + offset) /(float2) size;
  
  modelPos.y = sin(uv.y * PI - PI / 2.0f);
  modelPos.x = cos(uv.x * 2.0 * PI) * cos(uv.y * PI - PI / 2.0);
  modelPos.z = sin(uv.x * 2.0 * PI) * cos(uv.y * PI - PI / 2.0);
  
  
  if (uv.x < 0.0f || uv.x > 1.0f || uv.y < 0.0f || uv.y > 1.0f)
  {
    uv.x = 0.5f + atan2(modelPos.z, modelPos.x) / (2.0f * PI);
    uv.y = 0.5f - asin(modelPos.y) / PI;
  
    modelPos.y = sin(uv.y * PI - PI / 2.0f);
    modelPos.x = cos(uv.x * 2.0 * PI) * cos(uv.y * PI - PI / 2.0);
    modelPos.z = sin(uv.x * 2.0 * PI) * cos(uv.y * PI - PI / 2.0);
  }
  
  modelPos = normalize(modelPos);
  
  modelPos = modelPos + modelPos * heightMap[int2(uv * size)];
  
  return modelPos;
}


void CalcNormal(int x, int y, uint width, uint height)
{
  int2 target = { x, y };
  float2 size = { 2.0f, 0.0f };
  int3 off = { -1.0f, 0.0f, 1.0f };
  int2 texSize = { width, height };
  
  int2 offxy = off.xy;
  int2 offzy = off.zy;
  int2 offyx = off.yx;
  int2 offyz = off.yz;
  
  float s01 = heightMap[target + offxy].r;
  float s21 = heightMap[target + offzy].r;
  float s10 = heightMap[target + offyx].r;
  float s12 = heightMap[target + offyz].r;
  
  float3 va = { size.x, size.y, s21 - s01 };
  float3 vb = { size.y, size.x, s12 - s10 };
  
  va = normalize(va);
  vb = normalize(vb);
  
  float3 bump = normalize(cross(va, vb));
  
  float2 uv1, uv2, uv3;
  
  float3 v1 = GetModelPosisitonFromThreadID(target, int2(0, 0), texSize, uv1);
  float3 v2 = GetModelPosisitonFromThreadID(target, offxy, texSize, uv2);
  float3 v3 = GetModelPosisitonFromThreadID(target, offyz, texSize, uv3);
  
  float3 e1 = v2 - v1;
  float3 e2 = v3 - v1;
  float3 normal = normalize(cross(e2, e1));
  float2 tuv0 = uv2 - uv1;
  float2 tuv1 = uv3 - uv1;
  float den = 1.0f / (tuv0.x * tuv1.y - tuv1.x * tuv0.y);
  
  float3 tangent;
  tangent.x = (tuv1.y * e1.x - tuv0.y * e2.x) * den;
  tangent.y = (tuv1.y * e1.y - tuv0.y * e2.y) * den;
  tangent.z = (tuv1.y * e1.z - tuv0.y * e2.z) * den;
  tangent = normalize(tangent);
  float3 binormal;
  binormal.x = (-tuv1.x * e1.x - tuv0.x * e2.x) * den;
  binormal.y = (-tuv1.x * e1.y - tuv0.x * e2.y) * den;
  binormal.z = (-tuv1.x * e1.z - tuv0.x * e2.z) * den;
  binormal = normalize(binormal);
  float3 bumpNormal;
  bumpNormal = normalize((bump.x * tangent) + (bump.y * binormal) + (bump.z * normal));
  bumpMap[target] = float4(bumpNormal, 0.0f);
  //bumpMap[target] = float4(normal, 0);
}

[numthreads(1, 1, 1)]
void main(uint3 dispatchThreadId : SV_DispatchThreadID)
{
  int x = dispatchThreadId.x;
  int y = dispatchThreadId.y;
  uint width, height;
  heightMap.GetDimensions(width, height);
  CalcNormal(x, y, width, height);
}