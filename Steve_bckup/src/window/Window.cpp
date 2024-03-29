#include "Window.h"
#include "../events/Event.h"
#include <assert.h>
#include <imgui/imgui.h>

bool Window::IMGUI_READY = false;

Window::Window(uint x, uint y, const std::string& title)
    : myTitle(title)
{
  const WCHAR* CLASS_NAME   = L"aWndClass";
  WNDCLASSW    windowClass  = {};
  windowClass.style         = 0;
  windowClass.lpfnWndProc   = &Window::PreWndProc;
  windowClass.cbClsExtra    = 0;
  windowClass.cbWndExtra    = 0;
  windowClass.hInstance     = GetModuleHandleW(NULL);
  windowClass.hIcon         = NULL;
  windowClass.hCursor       = 0;
  windowClass.hbrBackground = 0;
  windowClass.lpszMenuName  = NULL;
  windowClass.lpszClassName = CLASS_NAME;

  auto val = RegisterClassW(&windowClass);
  assert(val);

  DWORD style   = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
  DWORD exStyle = WS_EX_OVERLAPPEDWINDOW;

  RECT rc = {0, 0, (LONG)x, (LONG)y};
  AdjustWindowRectEx(&rc, style, FALSE, exStyle);

  std::wstring wndTitle(myTitle.begin(), myTitle.end());

  myHwnd = CreateWindowEx(exStyle,
                          CLASS_NAME,
                          wndTitle.data(),
                          style,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          rc.right - rc.left,
                          rc.bottom - rc.top,
                          nullptr,
                          nullptr,
                          windowClass.hInstance,
                          this);

  POINT position = {80, 80};

  AdjustWindowRectEx(&rc, style, FALSE, exStyle);

  MoveWindow(myHwnd, position.x, position.y, rc.right - rc.left, rc.bottom - rc.top, true);

  GetClientRect(myHwnd, &rc);
  myIsOpen = true;
}

Window::~Window() { }

bool Window::ProcessEvent(UINT aMessage, WPARAM aWParam, LPARAM aLParam)
{
  Event::Message     m {};
  switch (aMessage)
  {
  case WM_KILLFOCUS:
  {
    m.EventType = Event::LostFocus;
    Event::PushMessage(m);
    return true;
  }
  case WM_SETFOCUS:
  {
    m.EventType = Event::GainedFocus;
    Event::PushMessage(m);
    return true;
  }
  case WM_DESTROY:
  {
    PostQuitMessage(0);
    myIsOpen = false;
    break;
  }
  case WM_KEYDOWN:
  {
    m.EventType        = Event::KeyDown;
    m.KeyEvent.KeyCode = static_cast<uint16>(aWParam);
    Event::PushMessage(m);
    return true;
  }
  case WM_KEYUP:
  {
    m.EventType        = Event::KeyUp;
    m.KeyEvent.KeyCode = static_cast<uint16>(aWParam);
    Event::PushMessage(m);
    return true;
  }
  case WM_CHAR:
  {
    /*EventTextTyped* ev_p = new EventTextTyped();
    ev_p->KeyCode        = static_cast<uint>(aWParam);
    ev_p->Signal();*/
    return true;
  }

  case WM_RBUTTONDOWN:
  case WM_LBUTTONDOWN:
  case WM_MBUTTONDOWN:
  {
    m.EventType = Event::MousePressed;
    m.MouseEvent.MousePosition.x = LOWORD(aLParam);
    m.MouseEvent.MousePosition.y = HIWORD(aLParam);
    m.MouseEvent.MouseButton = aWParam & 0xffff;

    if (Window::IMGUI_READY)
    {
      ImGuiIO& io = ImGui::GetIO();

      if (m.MouseEvent.MouseButton & MK_LBUTTON)
        io.AddMouseButtonEvent(0, true);
    }
    Event::PushMessage(m);
    return true;
  }
  case WM_RBUTTONUP:
  case WM_LBUTTONUP:
  case WM_MBUTTONUP:
  {
    m.EventType                  = Event::MouseReleased;
    m.MouseEvent.MousePosition.x = LOWORD(aLParam);
    m.MouseEvent.MousePosition.y = HIWORD(aLParam);
    m.MouseEvent.MouseButton     = aWParam & 0xffff;

    if (Window::IMGUI_READY)
    {
      ImGuiIO& io = ImGui::GetIO();

      if (m.MouseEvent.MouseButton & MK_LBUTTON)
        io.AddMouseButtonEvent(0, false);
    }
    Event::PushMessage(m);
    return true;
  }
  case WM_MOUSEMOVE:
  {
    m.EventType = Event::MouseMoved;
    m.MouseEvent.MousePosition.x = LOWORD(aLParam);
    m.MouseEvent.MousePosition.y = HIWORD(aLParam);
    m.MouseEvent.MouseDelta      = m.MouseEvent.MousePosition - myLastMousePosition;
    Event::PushMessage(m);
    return true;
  }
    /* case WM_MOUSEWHEEL:
  {
    EventMouseWheel* ev_p = new EventMouseWheel();
    ev_p->Delta           = GET_WHEEL_DELTA_WPARAM(aWParam);
    ev_p->Signal();
    return true;
  }*/
  }

  return false;
}

bool Window::IsOpen() const
{
  return myIsOpen;
}

void Window::SetFullscreen(bool isFullscreen) { }

Vector2u Window::GetSize() const
{

  return Vector2u(1920 / 2, 1080 / 2);
}

void Window::SetMousePosition(int x, int y)
{
  POINT pt;
  pt.x = x;
  pt.y = y;
  ClientToScreen(myHwnd, &pt);
  SetCursorPos(pt.x, pt.y);
}

void Window::PollEvents()
{
  MSG message = {0};
  while (PeekMessageW(&message, NULL, 0, 0, PM_REMOVE))
  {
    TranslateMessage(&message);
    DispatchMessageW(&message);
  }
}

HWND Window::GetHwnd() const
{
  return myHwnd;
}

////////////////////////////////////////////////////
LRESULT CALLBACK procProxy(HWND aHandle, UINT aMessage, WPARAM aWParam, LPARAM aLParam)
{
  Window* window_p = (Window*)GetWindowLongPtrW(aHandle, GWLP_USERDATA);

  if (window_p->ProcessEvent(aMessage, aWParam, aLParam))
  {
    return 0;
  }

  return DefWindowProcW(aHandle, aMessage, aWParam, aLParam);
}
////////////////////////////////////////////////////

LRESULT Window::PreWndProc(HWND aHwnd, UINT aMessage, WPARAM aWParam, LPARAM aLParam)
{
  if (aMessage == WM_CREATE)
  {
    CREATESTRUCT* pCreate = (CREATESTRUCT*)aLParam;

    SetWindowLongPtrW(aHwnd, GWLP_USERDATA, (LONG_PTR)pCreate->lpCreateParams);
    SetWindowLongPtrW(aHwnd, GWLP_WNDPROC, (LONG_PTR)procProxy);

    return 0;
  }

  return DefWindowProcW(aHwnd, aMessage, aWParam, aLParam);
}
