#pragma once

class Vec3;

template <class T>
class Vec2
{
public:
  Vec2(T _x, T _y);
  Vec2(const Vec2<T> vec2 = Vec2());
  template <class U>
  Vec2(const Vec2<U>& vec2);
  

  union
  {
    struct
    {
      T x;
      union
      {
        T y;
        T z;
      };
    };
    T data[2];
  };
};