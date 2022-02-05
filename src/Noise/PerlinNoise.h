#pragma once

#include "../utility/Typedef.h"
#include <string>
#include <vector>

class PerlinNoise
{
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