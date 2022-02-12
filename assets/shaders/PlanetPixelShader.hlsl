SamplerState aSampler : register(s0);
Texture2D<float4> diffuseTexture : register(t2);

cbuffer cbv2 : register(b3)
{
  float4 waterLevel;
}

struct Vertex
{
  float4 worldPos : WORLD_POS;
  float4 pos : SV_POSITION;
  float4 col : COLOR;
  float4 uv : TEXCOORD;
  float4 nor : NORMAL;
};

float4 main(Vertex vertex)
    : SV_TARGET
{
  // X: 0.917060, Y: -0.398749, Z: 0.000000
  float3 lightDir = normalize(float3(-0.917060, -0.398749, 0.000000));
  float3 color = diffuseTexture.Sample(aSampler, vertex.uv.xy).rgb * vertex.col.rgb;
  float4 pos = vertex.pos;
  float3 ambient = float3(0.05f, 0.05f, 0.05f);
  float3 finalColor = max(dot(normalize(vertex.nor.xyz), -lightDir), ambient) * color;
  //float3 finalColor = color;
  
  float3 white = float3(1, 1, 1);
  
  float h = length(vertex.worldPos.xyz);
  float w = (waterLevel.x + 1.0f) * 10.0f;
  if (h < w)
  {
    float d = 1.0f - ((w - h) / w);
    finalColor = finalColor * (white * d);
  }
  
  
  return saturate(float4(finalColor, 1.0f));
  //return (float4(vertex.nor.xyz + finalColor.xyz * 0.0f, 1.0f));
  //return float4(color, 1.0f);
}