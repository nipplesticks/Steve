#pragma once
#include <Common/Transform.h>

namespace Render
{
  struct View
  {
    View()
    {
      fov           = 75.f;
      width         = 1280.0f;
      height        = 720.0f;
      nearPlane     = 0.1f;
      farPlane      = 100000.0f;
      isPerspective = true;
    }
    float fov;
    float width;
    float height;
    float nearPlane;
    float farPlane;
    bool  isPerspective;
  };

  class Camera : public Transform
  {
  public:
    Camera();
    ~Camera();

    DM::Mat4x4f GetViewMatrix() const;
    const DM::Mat4x4f& GetProjectionMatrix() const;
    DM::Mat4x4f GetViewProjectionMatrix() const;
    void        SetView(const View& view);
    const View& GetView() const;

  private:
    View myView;
    DM::Mat4x4f myProjectionMatrix;
  };
} // namespace Render