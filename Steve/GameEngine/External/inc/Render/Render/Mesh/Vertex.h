#pragma once

#include <Common/DMath.h>

//#define USE_DIRECT_X_VERTEX

namespace Render
{
  struct Vertex
  {
    DM::Vec4fA position;
    DM::Vec4fA normal;
    DM::Vec2fA uv;
  };
  struct VertexLight
  {
    DM::Vec4fA position;
    DM::Vec2fA uv;
  };
  struct VertexEx
  {
    DM::Vec4fA position;
    DM::Vec4fA normal;
    DM::Vec2fA uv;
    DM::Vec4fA tangent;
    DM::Vec4fA bitangent;
  };
  struct Triangle
  {
    Vertex A;
    Vertex B;
    Vertex C;
  };
  struct TriangleLight
  {
    VertexLight A;
    VertexLight B;
    VertexLight C;
  };
  struct TriangleEx
  {
    VertexEx A;
    VertexEx B;
    VertexEx C;
  };

} // namespace Render