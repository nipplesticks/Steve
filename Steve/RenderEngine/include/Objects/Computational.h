#pragma once
#include <vector>
namespace Render
{
  class ResourceDescriptorHeap;
  class ComputationalPipelineState;
  class Resource;
  class Computational
  {
  public:
    Computational();
    virtual ~Computational();

    ResourceDescriptorHeap* GetResourceDescHeap() const;
    ComputationalPipelineState* GetComputationalPipelineState() const;


  private:
    ResourceDescriptorHeap*     myResourceDescHeap_p   = nullptr;
    ComputationalPipelineState* myComputationalState_p = nullptr;
    //std::vector<Resource*>      myResources;
  }
} // namespace Render