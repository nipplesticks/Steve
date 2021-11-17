#include "Window.h"
#include <assert.h>

Window::Window(uint x, uint y, const std::string& title) :
  myTitle(title)
{
  const WCHAR* CLASS_NAME = L"aWndClass";
  WNDCLASSW windowClass = {};
  windowClass.style = 0;
  windowClass.lpfnWndProc = &Window::PreWndProc;
  windowClass.cbClsExtra = 0;
  windowClass.cbWndExtra = 0;
  windowClass.hInstance = GetModuleHandleW(NULL);
  windowClass.hIcon = NULL;
  windowClass.hCursor = 0;
  windowClass.hbrBackground = 0;
  windowClass.lpszMenuName = NULL;
  windowClass.lpszClassName = CLASS_NAME;

  auto val = RegisterClassW(&windowClass);
  assert(val);

  DWORD style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
  DWORD exStyle = WS_EX_OVERLAPPEDWINDOW;

  RECT rc = { 0, 0, x, y };
  AdjustWindowRectEx(&rc,
    style,
    FALSE,
    exStyle);

  std::wstring wndTitle(myTitle.begin(), myTitle.end());

  myHwnd = CreateWindowEx(
    exStyle,
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

  POINT position = { 0 };

  AdjustWindowRectEx(&rc, style, FALSE, exStyle);

  MoveWindow(
    myHwnd,
    position.x, position.y,
    rc.right - rc.left,
    rc.bottom - rc.top,
    true
  );

  GetClientRect(myHwnd, &rc);
  myIsOpen = true;
}

Window::~Window()
{

}

bool Window::ProcessEvent(UINT aMessage, WPARAM aWParam, LPARAM aLParam)
{
  switch (aMessage)
  {
  case WM_DESTROY:
    PostQuitMessage(0);
    myIsOpen = false;
    break;
  }

  return false;
}

bool Window::IsOpen() const
{
  return myIsOpen;
}

void Window::SetFullscreen(bool isFullscreen)
{

}

Vector2u Window::GetSize() const
{

  return Vector2u();
}

void Window::PollEvents()
{
  MSG message = { 0 };
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
