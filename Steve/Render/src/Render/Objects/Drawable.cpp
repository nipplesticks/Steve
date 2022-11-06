#include "pch.h"
#include "Render/Objects/Drawable.h"
#include "Render/Renderer.h"

using namespace Render;

std::vector<Drawable*> Drawable::gDrawQueue;

struct MatrixConstantBuffer
{
  DM::Mat4x4f worldMatrix;
  DM::Mat4x4f worldMatrixInverse;
};

Render::Drawable::Drawable()
    : Transform()
{ }
Render::Drawable::~Drawable() { }
void Render::Drawable::SetMesh(Mesh* mesh_p)
{
  myMesh_p = mesh_p;
}
void Render::Drawable::SetGraphicalPipelineState(GraphicalPipelineState* graphicPipelineState_p)
{
  myGraphicsState_p = graphicPipelineState_p;
}
void Render::Drawable::CreateGPUData()
{
  myConstantBuffer.Create("Drawable_Constant_buffer", sizeof(MatrixConstantBuffer));
  myResourceDescHeap.CreateAndBindResources(
      "Drawable_Resource_Heap",
      {Renderer::GetInstance()->GetCameraConstantBuffer(), &myConstantBuffer},
      myMesh_p->GetTextures(),
      {});
}
void Render::Drawable::UpdateConstantbuffer()
{
  MatrixConstantBuffer mcb;
  mcb.worldMatrix        = GetWorldMatrix();
  mcb.worldMatrixInverse = GetInverseWorldMatrix();
  myConstantBuffer.Update(&mcb, D3D12_RESOURCE_STATE_GENERIC_READ, sizeof(mcb));
}

void Render::Drawable::Draw()
{
  gDrawQueue.push_back(this);
}

Mesh* Render::Drawable::GetMesh()
{
  return myMesh_p;
}
GraphicalPipelineState* Render::Drawable::GetGraphicalPipelineState()
{
  return myGraphicsState_p;
}
ResourceDescriptorHeap* Render::Drawable::GetResourceDescriptorHeap()
{
  return &myResourceDescHeap;
}
ConstantBuffer* Render::Drawable::GetConstantBuffer()
{
  return &myConstantBuffer;
}