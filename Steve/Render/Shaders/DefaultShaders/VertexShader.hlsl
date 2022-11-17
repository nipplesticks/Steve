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
  output.worldPosition = mul(input.position, transpose(worldMatrices.worldMatrix));
  output.position =
      mul(output.worldPosition, transpose(mul(cameraBuffer.projection, cameraBuffer.view)));
  output.normal    = normalize(mul(input.normal, transpose(worldMatrices.worldMatrix)));
  output.tangent   = normalize(mul(input.tangent, transpose(worldMatrices.worldMatrix)));
  output.bitangent = normalize(mul(input.bitangent, transpose(worldMatrices.worldMatrix)));
  output.uv        = input.uv;
  return output;
}