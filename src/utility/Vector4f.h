#pragma once

struct Vector4f
{
  Vector4f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f, float _w = 0.0f)
  {
    x = _x;
    y = _y;
    z = _z;
    w = _w;

  }
  float x, y, z, w;
};