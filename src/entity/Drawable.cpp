#include "Drawable.h"
#include "../renderer/mesh/Mesh.h"
#include "../renderer/buffers/TextureBuffer.h"
#include "../renderer/d3d12/GraphicsPipelineState.h"
#include "../renderer/camera/Camera.h"
#include "../utility/UtilityFuncs.h"

std::unordered_map<GraphicsPipelineState*, Drawable::DrawQueue> Drawable::DRAW_QUEUE;

Drawable::Drawable(const DM::Vec3f& position)
    : Transform(position)
{
  myWorldConstantBuffer.Init(sizeof(DM::Mat4x4));
  DM::Mat4x4 world = GetWorldMatrix();
  myWorldConstantBuffer.Update(&world, sizeof(DM::Mat4x4));
}

void Drawable::SetMesh(Mesh* mesh_p)
{
  myMesh_p = mesh_p;
}

void Drawable::SetTexture(TextureBuffer* textureBuffer_p)
{
  myTextureBuffer_p = textureBuffer_p;
}

void Drawable::SetGraphicsPipelineState(GraphicsPipelineState* state_p)
{
  myGraphicsState_p = state_p;
}

void Drawable::Bind()
{
  if (myIsBinded)
    ASSERT_STR(false, "Object is already binded...\n");

  myResourceDescHeap.Create({&Camera::VIEW_PROJECTION_CB, &myWorldConstantBuffer}, {myTextureBuffer_p});
  myIsBinded = true;
}

void Drawable::UpdateConstantBuffer()
{
  DM::Mat4x4 world = GetWorldMatrix();
  myWorldConstantBuffer.Update(&world, sizeof(DM::Mat4x4));
}

void Drawable::Draw()
{
  ASSERT_STR(myMesh_p && myGraphicsState_p,
             "myMesh_p=%p or myGraphicsState_p=%p is nullptr\n",
             (void*)myMesh_p,
             (void*)myGraphicsState_p);
  ASSERT_STR(myIsBinded, "Object is not binded...\n");
  PushDrawableToDrawQueue(this);
}

Mesh* Drawable::GetMesh() const
{
  return myMesh_p;
}

TextureBuffer* Drawable::GetTextureBuffer() const
{
  return myTextureBuffer_p;
}

GraphicsPipelineState* Drawable::GetGraphicsPipelineState() const
{
  return myGraphicsState_p;
}

const ResourceDescriptorHeap& Drawable::GetResourceDescHeap() const
{
  return myResourceDescHeap;
}

void Drawable::PushDrawableToDrawQueue(Drawable* drawable)
{
  DRAW_QUEUE[drawable->myGraphicsState_p].Push(drawable);
}
