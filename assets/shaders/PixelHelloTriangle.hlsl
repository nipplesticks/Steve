SamplerState aSampler : register(s0);
Texture2D<float4> aTexture : register(t0);

struct Vertex
{
  float4 pos : SV_POSITION;
  float4 col : COLOR;
  float4 nor : NORMAL;
  float4 uv : TEXCOORD;
};

float4 main(Vertex vertex)
    : SV_TARGET
{
  // X: 0.917060, Y: -0.398749, Z: 0.000000
  float3 lightDir = normalize(float3(-0.917060, -0.398749, 0.000000));
  //float3 lightDir = normalize(float3(0, 0, -1.000000));
  float3 color = aTexture.Sample(aSampler, vertex.uv.xy).rgb * vertex.col.rgb;
    //color = vertex.col.rgb;
  float4 pos = vertex.pos;
  float3 ambient = float3(0.05f, 0.05f, 0.05f);

  float3 finalColor = max(dot(normalize(vertex.nor.xyz), -lightDir), ambient) * color;
  
  //return float4(vertex.col.rgb, 1);
  return saturate(float4(finalColor, 1.0f));
  //return float4(color, 1.0f);
  //return float4(pos.x, pos.y, pos.z, 1.0f);
  //return float4(vertex.uv.x, vertex.uv.y, 1.0f, 1.0f);
}