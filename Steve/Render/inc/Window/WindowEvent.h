#pragma once
#include <Common/Typedef.h>
#include <Common/DMath.h>
#include <unordered_map>

namespace Render
{

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
      // Gamepad Events
      ButtonDown,
      ButtonUp,
      Trigger,
      // Window Events
      LostFocus,
      GainedFocus,
      Resize,
      WindowMoved,
      NREVENTS
    };

    struct Mouse
    {
      DM::Vec2i MousePosition;
      union
      {
        int       WheelDelta;
        DM::Vec2i MouseDelta;
        uint32    MouseButton;
      };
    };

    struct Keyboard
    {
      uint16 KeyCode;
    };

    struct Window
    {
      union
      {
        struct
        {
          DM::Vec2u NewWindowSize;
          bool      isFullscreen;
        };
        DM::Vec2i Position;
      };
    };

    struct Message
    {
      Type EventType;
      union
      {
        Mouse    MouseEvent;
        Keyboard KeyEvent;
        Window   WindowEvent;
        /*...*/
      };
    };

    class Subscriber
    {
    public:
      Subscriber() = default;
      Subscriber(const Subscriber& other);
      ~Subscriber();

      void Subscribe(Event::Type eventType);
      void UnSubscribe(Event::Type eventType);
      void UnSubscribeAll();

      Subscriber&  operator=(const Subscriber& other);
      virtual void HandleEvent(const Event::Message& message) = 0;

    private:
      void _copy(const Subscriber& other);

    private:
      std::unordered_map<Type, bool> mySubscriptions;
    };

    class EventHandler
    {
    public:
      static void PushMessage(Event::Message message);
      static void HandleEvents();
      static void StartSubscription(Event::Type type, Subscriber* subscriber_p);
      static void CancelSubscription(Event::Type type, Subscriber* subscriber_p);

    private:
      static std::vector<Event::Message>                                            myEventQueue;
      static std::unordered_map<Event::Type, std::unordered_map<Subscriber*, bool>> mySubscribers;
      static bool                                                                   SkipEvents;
    };

  } // namespace Event
} // namespace Render