#pragma once

#include <Common/DMath.h>

namespace Render
{
  struct Vertex
  {
    DM::Vec4f position;
    DM::Vec4f normal;
    DM::Vec4f uv;
  };
  struct VertexEx
  {
    DM::Vec4f position;
    DM::Vec4f normal;
    DM::Vec4f uv;
    DM::Vec4f tangent;
    DM::Vec4f bitangent;
  };
  struct Triangle
  {
    Vertex A;
    Vertex B;
    Vertex C;
  };
  struct TriangleEx
  {
    VertexEx A;
    VertexEx B;
    VertexEx C;
  };
}