#pragma once

#include "../utility/Typedef.h"
#include <string>
#include <vector>
/*
height.frequency   = 1.0f;
      height.iterations  = 1;
      height.exponent    = 1.0f;
      height.fudgeFactor = 1.0f;

      moisture.frequency   = 1.0f;
      moisture.iterations  = 1;
      moisture.exponent    = 1.0f;
      moisture.fudgeFactor = 1.0f;
      waterLevel           = 0.1f;
      texWidth             = 512;
      texHeight            = 512;
      seed                 = 1337;
*/
struct Noise
{
  Noise(uint _seed = 1337, float _frequency = 1.0f, float _exponent = 1.0f, float _fudgeFactor = 1.0f, uint _iterations = 1)
  {
    seed = _seed;
    frequency = _frequency;
    expnoent  = _exponent;
    fudgeFactor = _fudgeFactor;
    iterations  = _iterations;
  }
  uint  seed;
  float frequency;
  float expnoent;
  float fudgeFactor;
  uint  iterations;
};

class PerlinNoise
{
public:

public:
  PerlinNoise();
  PerlinNoise(uint seed);
  PerlinNoise(const std::string& seed);
  double Sample(double x, double y, double z);
  std::vector<int> GetPermutaion();

private:
  void  _init(uint seed);
  double _fade(double t);
  double _lerp(double t, double a, double b);
  double _grad(int hash, double x, double y, double z);

private:
  std::vector<int> myPermutation;

};