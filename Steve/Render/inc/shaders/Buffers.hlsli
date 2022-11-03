struct CameraBuffer
{
  float4x4 view;
  float4x4 projection;
  float4   position;
};

struct WorldMatrices
{
  float4x4 worldMatrix;
  float4x4 worldMatrixInverse;
};