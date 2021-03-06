#include "PerlinNoise.h"
#include <algorithm>
#include <cmath>
#include <numeric>
#include <random>

PerlinNoise::PerlinNoise()
{
  _init(0);
}

PerlinNoise::PerlinNoise(uint seed)
{
  _init(seed);
}

PerlinNoise::PerlinNoise(const std::string& seed)
{
  std::string _s        = seed;
  int         finalSeed = 0;
  uint        i         = 0;
  for (auto& c : seed)
  {
    _s[i++] = std::to_string(((int)c))[0];
  }
  if (i > 0)
  {
    finalSeed = std::atoi(_s.c_str());
  }
  _init(finalSeed);
}

double PerlinNoise::Sample(double x, double y, double z)
{
  int _x = (int)floor(x) & 255;
  int _y = (int)floor(y) & 255;
  int _z = (int)floor(z) & 255;

  x -= floor(x);
  y -= floor(y);
  z -= floor(z);

  double u = _fade(x);
  double v = _fade(y);
  double w = _fade(z);

  int A  = myPermutation[(uint)(_x) % 256] + _y;
  int AA = myPermutation[(uint)(A) % 256] + _z;
  int AB = myPermutation[(uint)(A + 1) % 256] + _z;
  int B  = myPermutation[(uint)(_x + 1) % 256] + _y;
  int BA = myPermutation[(uint)(B) % 256] + _z;
  int BB = myPermutation[(uint)(B + 1) % 256] + _z;

  double res = _lerp(w,
                     _lerp(v,
                           _lerp(u,
                                 _grad(myPermutation[(uint)(AA) % 256], x, y, z),
                                 _grad(myPermutation[(uint)(BA) % 256], x - 1, y, z)),
                           _lerp(u,
                                 _grad(myPermutation[(uint)(AB) % 256], x, y - 1, z),
                                 _grad(myPermutation[(uint)(BB) % 256], x - 1, y - 1, z))),
                     _lerp(v,
                           _lerp(u,
                                 _grad(myPermutation[(uint)(AA + 1) % 256], x, y, z - 1),
                                 _grad(myPermutation[(uint)(BA + 1) % 256], x - 1, y, z - 1)),
                           _lerp(u,
                                 _grad(myPermutation[(uint)(AB + 1) % 256], x, y - 1, z - 1),
                                 _grad(myPermutation[(uint)(BB + 1) % 256], x - 1, y - 1, z - 1))));

  return (res + 1.0f) / 2.0f;
}

std::vector<int> PerlinNoise::GetPermutaion()
{
  return myPermutation;
}

void PerlinNoise::_init(uint seed)
{
  myPermutation.resize(256);
  std::iota(myPermutation.begin(), myPermutation.end(), 0);
  std::default_random_engine engine(seed);
  std::shuffle(myPermutation.begin(), myPermutation.end(), engine);
}

double PerlinNoise::_fade(double t)
{
  return t * t * t * (t * (t * 6 - 15) + 10);
}

double PerlinNoise::_lerp(double t, double a, double b)
{
  return a + t * (b - a);
}

double PerlinNoise::_grad(int hash, double x, double y, double z)
{
  int h = hash & 15;
  // Convert lower 4 bits of hash into 12 gradient directions
  double u = h < 8 ? x : y, v = h < 4 ? y : h == 12 || h == 14 ? x : z;
  return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}
