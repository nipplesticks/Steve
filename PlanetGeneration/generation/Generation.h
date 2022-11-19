#pragma once

#include <common/DMath.h>
#include <common/Typedef.h>
#include <common/AssertX.h>
#include <fstream>
#include <string>
#include <vector>

constexpr uint32 ICOSAHEDRON_SIDES = 20;

struct Triangle
{
  Triangle(uint32 a = 0u, uint32 b = 0u, uint32 c = 0u)
  {
    A = a;
    B = b;
    C = c;
  }
  uint32& operator[](uint32 idx)
  {
    return data[idx];
  }

  union
  {
    struct
    {
      uint32 A, B, C;
    };
    uint32 data[3];
  };
};

struct Vertex
{
  DM::Vec4f position;
  DM::Vec4f normal;
  DM::Vec4f uv;
};

struct DetailLevelDuringCreation
{
  std::vector<DM::Vec3f> points;
  std::vector<Triangle>  triangles;
  uint32                 detailLevel;
};
struct IcosahedronSide
{
  std::vector<DetailLevelDuringCreation> detailLevels;
};

struct DetailLevel
{
  std::vector<Vertex> vertices;
  std::vector<uint32> indices;
};

struct SphereSide
{
  std::vector<DetailLevel> detailLevel;
};

struct Sphere
{
  SphereSide sides[ICOSAHEDRON_SIDES];
};

class Generation
{
private:
  Generation() = default;
  ~Generation() = default;

public:
  static void Create(const std::string&         path,
              uint32                     qualityLevel,
              const std::vector<uint32>& qualityLevels = {});

};