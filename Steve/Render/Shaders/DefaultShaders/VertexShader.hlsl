#include "Datatypes.hlsli"
#include "../Buffers.hlsli"

cbuffer cbv0 : register(b0)
{
  CameraBuffer cameraBuffer;
};
cbuffer cbv1 : register(b1)
{
  WorldMatrices worldMatrices;
};

VS_OUT main(VS_IN input)
{
  VS_OUT output;
  output.worldPosition = mul(input.position, worldMatrices.worldMatrix);
  output.position =
      mul(output.worldPosition, mul(cameraBuffer.view, cameraBuffer.projection));
  output.normal = normalize(mul(input.normal, worldMatrices.worldMatrix));
  output.tangent = normalize(mul(input.tangent, worldMatrices.worldMatrix));
  output.bitangent = normalize(mul(input.bitangent, worldMatrices.worldMatrix));
  output.uv        = input.uv;

  return output;
}