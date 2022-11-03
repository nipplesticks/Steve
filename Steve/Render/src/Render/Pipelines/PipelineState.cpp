#include "pch.h"
#include "Render/Pipelines/PipelineState.h"

ID3D12PipelineState* Render::PipelineState::GetPipelineState() const
{
  return myPipelineState_p;
}
