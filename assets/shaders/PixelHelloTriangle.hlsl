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
  return vertex.nor;
}