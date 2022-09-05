struct VS_IN
{
  float4 position : SV_POSITION;
  float2 uv : TEXCOORD;
};

VS_IN main( VS_IN vIn)
{
  return vIn;
}