struct VS_OUT
{
  float4 pos : SV_POSITION;
  float4 nor : NORMAL;
  float4 uv : TEXCOORD;
};

float4 main(VS_OUT vIn) : SV_TARGET
{
  
  return float4(0.976f, 0.843f, 0.109f, 1.0f);
}