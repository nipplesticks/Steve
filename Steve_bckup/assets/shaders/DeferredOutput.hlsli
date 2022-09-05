#define FLT_MAX 3.402823466e+38F
#define DEFERRED_PICKABLE_ID_DEFUALT 0xffffffff
#define DEFERRED_FLOAT4_DEFAULT float4(FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX)

struct DeferredOutput
{
  float4 position : SV_TARGET0;
  float4 normal : SV_TARGET1;
  float4 color : SV_TARGET2;
  uint pickableId : SV_TARGET3;
};

void GetDefaultDeferredOutput(out DeferredOutput output)
{
  output.color = DEFERRED_FLOAT4_DEFAULT;
  output.normal = DEFERRED_FLOAT4_DEFAULT;
  output.position = DEFERRED_FLOAT4_DEFAULT;
  output.pickableId = DEFERRED_PICKABLE_ID_DEFUALT;
}