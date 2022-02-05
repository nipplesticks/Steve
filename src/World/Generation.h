#pragma once

#include "../utility/Typedef.h"
#include "../utility/DMath.h"
#include "../Noise/PerlinNoise.h"
#include "../renderer/buffers/ConstantBuffer.h"
#include "../utility/UtilityFuncs.h"

struct Generation
{
  float frequency = 1.0f;
  float exponent = 1.0f;
  float fudgeFactor = 1.0f;
  uint  iterations = 1;
  DM::Vec4f textureSize;
};

class GenerationGPU
{
public:
  GenerationGPU()
  {
    generationCB.Init(sizeof(Generation));
    permutationCB.Init(sizeof(int) * 256);
  }
  void GeneratePermutation(uint seed) {
    PerlinNoise pn(seed);
    permutation      = pn.GetPermutaion();
    ASSERT(permutation.size() == 256);
  }
  void Upload()
  {
    generationCB.Update(&generation, sizeof(Generation));
    permutationCB.Update(permutation.data(), sizeof(int) * (uint)permutation.size());
  }
  std::vector<int> permutation;
  Generation  generation;
  ConstantBuffer generationCB;
  ConstantBuffer permutationCB;


};