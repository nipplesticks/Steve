struct DeferredOutput
{
  float4 position : SV_TARGET0;
  float4 normal : SV_TARGET1;
  float4 color : SV_TARGET2;
  uint pickableId : SV_TARGET3;
};