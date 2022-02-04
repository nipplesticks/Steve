float _fade(float t)
{
  return t * t * t * (t * (t * 6 - 15) + 10);
}

float _lerp(float t, float a, float b)
{
  return a + t * (b - a);
}

float _grad(int hash, float x, float y, float z)
{
  int h = hash & 15;
  // Convert lower 4 bits of hash into 12 gradient directions
  float u = h < 8 ? x : y, v = h < 4 ? y : h == 12 || h == 14 ? x : z;
  return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

float PerlineNoise(float x, float y, float z, int _permutation[256])
{
  int _x = (int) floor(x) & 255;
  int _y = (int) floor(y) & 255;
  int _z = (int) floor(z) & 255;

  x -= floor(x);
  y -= floor(y);
  z -= floor(z);
  
  float u = _fade(x);
  float v = _fade(y);
  float w = _fade(z);

  int A = _permutation[_x] + _y;
  int AA = _permutation[A] + _z;
  int AB = _permutation[A + 1] + _z;
  int B = _permutation[_x + 1] + _y;
  int BA = _permutation[B] + _z;
  int BB = _permutation[B + 1] + _z;
  
  float res = _lerp(
      w,
      _lerp(v,
            _lerp(u, _grad(_permutation[AA], x, y, z), _grad(_permutation[BA], x - 1, y, z)),
            _lerp(u,
                  _grad(_permutation[AB], x, y - 1, z),
                  _grad(_permutation[BB], x - 1, y - 1, z))),
      _lerp(v,
            _lerp(u,
                  _grad(_permutation[AA + 1], x, y, z - 1),
                  _grad(_permutation[BA + 1], x - 1, y, z - 1)),
            _lerp(u,
                  _grad(_permutation[AB + 1], x, y - 1, z - 1),
                  _grad(_permutation[BB + 1], x - 1, y - 1, z - 1))));

  return (res + 1.0f) / 2.0f;
}