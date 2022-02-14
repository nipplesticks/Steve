#include <iostream>
#include "renderer/d3d12/myRenderer.h"
#include "renderer/buffers/Resource.h"
#include "renderer/d3d12/ResourceDescriptorHeap.h"
#include "window/Window.h"

int main()
{
  Window wnd(1280, 720, "Steve in the house");
  MyRenderer::ENABLE_DEBUG_CONTROLLER = true;
  MyRenderer::Init(wnd.GetHwnd());
  MyRenderer* renderer_p = MyRenderer::GetInstance();

  struct dumdum
  {
    DM::Vec4f a;
    DM::Vec4f b;
  } dummy;

  std::vector<dumdum> vec(7);

  Resource    aResource;
  aResource.Init(Resource::Resource_Type::StructuredBuffer, sizeof(dummy) * vec.size(), DXGI_FORMAT_UNKNOWN, 1, 1, vec.size());

  aResource.UpdateNow(vec.data(), D3D12_RESOURCE_STATE_GENERIC_READ);

  ResourceDescriptorHeap resourceState;
  resourceState.CreateNew({}, {&aResource}, {});

  return 0;
}