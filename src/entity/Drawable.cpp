#include "Drawable.h"
#include "../renderer/buffers/Texture2D.h"
#include "../renderer/camera/Camera.h"
#include "../renderer/d3d12/GraphicsPipelineState.h"
#include "../renderer/mesh/Mesh.h"
#include "../utility/UtilityFuncs.h"

std::unordered_map<GraphicsPipelineState*, Drawable::DrawQueue> Drawable::DRAW_QUEUE;

Drawable::Drawable(const DM::Vec3f& position)
    : Transform(position)
{
  myWorldConstantBuffer.Create(sizeof(DM::Mat4x4f));
  DM::Mat4x4f world = GetWorldMatrix();
  myWorldConstantBuffer.UpdateNow(&world);
}

void Drawable::SetMesh(Mesh* mesh_p)
{
  myMesh_p = mesh_p;
}

void Drawable::SetTexture(Texture2D* textureBuffer_p)
{
  myTextureBuffer_p = textureBuffer_p;
}

void Drawable::SetGraphicsPipelineState(GraphicsPipelineState* state_p)
{
  myGraphicsState_p = state_p;
}

void Drawable::BindWithDefaultResourceDescHeap()
{
  myResourceDescHeap_p = new ResourceDescriptorHeap;
  myResourceDescHeap_p->Create(
      {&Camera::VIEW_PROJECTION_CB, &myWorldConstantBuffer}, {myTextureBuffer_p}, {});
}

void Drawable::SetCustomResourceDescriptorHeap(ResourceDescriptorHeap* customHeap_p)
{
  myResourceDescHeap_p = customHeap_p;
}

void Drawable::UpdateWorldMatrixConstantBuffer()
{
  DM::Mat4x4f world = GetWorldMatrix();
  myWorldConstantBuffer.UpdateNow(&world, D3D12_RESOURCE_STATE_GENERIC_READ);
}

ConstantBuffer* Drawable::GetWorldMatrixConstantBuffer() const
{
  return (ConstantBuffer*)&myWorldConstantBuffer;
}

void Drawable::Draw()
{
  ASSERT_STR(myMesh_p && myGraphicsState_p && myResourceDescHeap_p,
             "myMesh_p=%p or myGraphicsState_p=%p or myResourceDescHeap_p=%p is nullptr\n",
             (void*)myMesh_p,
             (void*)myGraphicsState_p,
             (void*)myResourceDescHeap_p);
  PushDrawableToDrawQueue(this);
}

Mesh* Drawable::GetMesh() const
{
  return myMesh_p;
}

Texture2D* Drawable::GetTextureBuffer() const
{
  return myTextureBuffer_p;
}

GraphicsPipelineState* Drawable::GetGraphicsPipelineState() const
{
  return myGraphicsState_p;
}

ResourceDescriptorHeap* Drawable::GetResourceDescHeap() const
{
  return myResourceDescHeap_p;
}

void Drawable::PushDrawableToDrawQueue(Drawable* drawable)
{
  DRAW_QUEUE[drawable->myGraphicsState_p].Push(drawable);
}
