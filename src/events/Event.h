#pragma once
#include "../utility/DMath.h"
#include "../utility/Typedef.h"

namespace Event
{
  enum Type
  {
    // Mouse Events
    MouseMoved = 0,
    MouseWheel,
    MousePressed,
    MouseReleased,
    // Key Events
    KeyDown,
    KeyUp,
    TextTyped,
    // Window Events
    LostFocus,
    GainedFocus,
    Resize,
    NREVENTS
  };

  struct InputMouseEvent
  {
    union
    {
      DM::Vec2i MousePosition;
      int       WheelDelta;
      union
      {
        DM::Vec2i   MouseDelta;
        uint MouseButton;
      };
    };
  };

  struct InputKeyEvent
  {
    uint16 KeyCode;
  };

  struct WindowEvent
  {
    union
    {
      DM::Vec2u NewWindowSize;
    };
  };

  struct Message
  {
    Type EventType;
    union
    {
      InputMouseEvent MouseEvent;
      InputKeyEvent   KeyEvent;
      WindowEvent     WindowEvent;
    };
  };

  void PushMessage(const Message& message);

} // namespace Event
