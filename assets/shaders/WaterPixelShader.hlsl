SamplerState aSampler : register(s0);
Texture2D<float4> distortion : register(t0);

struct VS_OUT
{
  float4 worldPos : WORLD_POS;
  float4 pos : SV_POSITION;
  float4 col : COLOR;
  float4 uv : TEXCOORD;
  float4 tangent : TANGENT;
  float4 bitangent : BITANGENT;
  float4 nor : NORMAL;
};

float4 main(VS_OUT vIn) : SV_TARGET
{
  float3 lightDir = normalize(float3(-0.917060, -0.398749, 0.000000));
  float3 T = normalize(vIn.tangent.xyz);
  float3 N = normalize(vIn.nor.xyz);
  float3 B = normalize(vIn.bitangent.xyz);
  float3x3 TBN = { T, B, N };
  
  float3 aNormal = distortion.Sample(aSampler, vIn.uv.xy).rgb;
  aNormal = aNormal * 2.0f - 1.0f;
  aNormal = normalize(mul(aNormal, (TBN)));
  
  float3 color = float3(0, 0, 1);
  float3 finalColor = dot(aNormal, -lightDir) * color;
  
  return float4(finalColor, 1.0f);
}