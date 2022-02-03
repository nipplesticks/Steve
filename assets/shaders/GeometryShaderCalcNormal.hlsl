struct GS_OUT
{
  float4 worldPos : WORLD_POS;
  float4 pos : SV_POSITION;
  float4 col : COLOR;
  float4 uv : TEXCOORD;
  float4 nor : NORMAL;
};

[maxvertexcount(3)]
void main(
  triangle GS_OUT input[3],
  inout TriangleStream<GS_OUT> output
)
{
  float4 normal;
  float3 v1 = input[0].worldPos.xyz;
  float3 v2 = input[1].worldPos.xyz;
  float3 v3 = input[2].worldPos.xyz;
  float3 e0 = v2 - v1;
  float3 e1 = v3 - v1;
  normal = float4(normalize(cross(e1, e0)), 0.0f);
  for (uint i = 0; i < 3; i++)
  {
    GS_OUT element;
    element.pos = input[i].pos;
    element.col = input[i].col;
    element.uv = input[i].uv;
    element.nor = normal;
    element.worldPos = input[i].worldPos;
    output.Append(element);
  }
}