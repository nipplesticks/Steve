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

float PerlineNoise(float xx, float yy, float zz, int _permutation[256])
{
  int _x = (int) floor(xx) & 255;
  int _y = (int) floor(yy) & 255;
  int _z = (int) floor(zz) & 255;

  float x = xx - floor(xx);
  float y = yy - floor(yy);
  float z = zz - floor(zz);

  float u = _fade(x);
  float v = _fade(y);
  float w = _fade(z);

  int A = _permutation[(uint) _x % 256] + _y;
  int AA = _permutation[(uint) A % 256] + _z;
  int AB = _permutation[(uint) (A + 1) % 256] + _z;
  int B = _permutation[(uint) (_x + 1) % 256] + _y;
  int BA = _permutation[(uint) B % 256] + _z;
  int BB = _permutation[(uint) (B + 1) % 256] + _z;

  float res = _lerp(
      w,
      _lerp(v,
            _lerp(u, _grad(_permutation[(uint) AA % 256], x, y, z), _grad(_permutation[(uint) BA % 256], x - 1, y, z)),
            _lerp(u,
                  _grad(_permutation[(uint) AB % 256], x, y - 1, z),
                  _grad(_permutation[(uint) BB % 256], x - 1, y - 1, z))),
      _lerp(v,
            _lerp(u,
                  _grad(_permutation[(uint) (AA + 1) % 256], x, y, z - 1),
                  _grad(_permutation[(uint) (BA + 1) % 256], x - 1, y, z - 1)),
            _lerp(u,
                  _grad(_permutation[(uint) (AB + 1) % 256], x, y - 1, z - 1),
                  _grad(_permutation[(uint) (BB + 1) % 256], x - 1, y - 1, z - 1))));

  return (res + 1.0f) / 2.0f;
}