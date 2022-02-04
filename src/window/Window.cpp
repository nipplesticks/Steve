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
  ImGuiIO  temp;
  ImGuiIO& io = temp;

  if (Window::IMGUI_READY)
    io = ImGui::GetIO();

  switch (aMessage)
  {
  case WM_DESTROY:
  {
    PostQuitMessage(0);
    myIsOpen = false;
    break;
  }
  case WM_KEYDOWN:
  {
    EventKeyDown* ev_p = new EventKeyDown();
    ev_p->KeyCode      = static_cast<uint16>(aWParam);
    ev_p->Signal();
    return true;
  }
  case WM_KEYUP:
  {
    EventKeyUp* ev_p = new EventKeyUp();
    ev_p->KeyCode      = static_cast<uint16>(aWParam);
    ev_p->Signal();
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
    uint               x = LOWORD(aLParam);
    uint               y = HIWORD(aLParam);
    DM::Vec2i          mp(x, y);
    EventMousePressed* ev_p = new EventMousePressed();

    ev_p->MousePosition  = mp;
    ev_p->MButtonPressed = aWParam & MK_MBUTTON;
    ev_p->LButtonPressed = aWParam & MK_LBUTTON;
    ev_p->RButtonPressed = aWParam & MK_RBUTTON;
    ev_p->Signal();

    if (ev_p->LButtonPressed)
      io.AddMouseButtonEvent(0, true);

    return true;
  }
  case WM_RBUTTONUP:
  case WM_LBUTTONUP:
  case WM_MBUTTONUP:
  {
    uint                x = LOWORD(aLParam);
    uint                y = HIWORD(aLParam);
    DM::Vec2i           mp(x, y);
    EventMouseReleased* ev_p = new EventMouseReleased();

    ev_p->MousePosition   = mp;
    ev_p->MButtonReleased = aMessage == WM_MBUTTONUP;
    ev_p->LButtonReleased = aMessage == WM_LBUTTONUP;
    ev_p->RButtonReleased = aMessage == WM_RBUTTONUP;
    ev_p->Signal();

    if (ev_p->LButtonReleased)
      io.AddMouseButtonEvent(0, false);

    return true;
  }
  case WM_MOUSEMOVE:
  {
    uint x = LOWORD(aLParam);
    uint y = HIWORD(aLParam);

    DM::Vec2i        mp(x, y);
    EventMouseMoved* ev_p = new EventMouseMoved();
    ev_p->MousePosition   = mp;
    ev_p->MouseDelta      = mp - myLastMousePosition;
    myLastMousePosition   = mp;
    ev_p->MButtonPressed  = aWParam & MK_MBUTTON;
    ev_p->LButtonPressed  = aWParam & MK_LBUTTON;
    ev_p->RButtonPressed  = aWParam & MK_RBUTTON;
    ev_p->Signal();

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
