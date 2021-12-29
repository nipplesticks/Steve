#pragma once
#include "../utility/Vector2u.h"
#define NOMINMAX
#include <Windows.h>
#include <string>
#include "../utility/DMath.h"

class Window
{
public:
  Window(uint x, uint y, const std::string& title = "");
  ~Window();

  bool ProcessEvent(UINT aMessage, WPARAM aWParam, LPARAM aLParam);
  bool IsOpen() const;

  void PollEvents();
  HWND GetHwnd() const;

  void     SetFullscreen(bool isFullscreen);
  Vector2u GetSize() const;

public:
  static LRESULT CALLBACK PreWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
  std::string myTitle;
  bool        myIsOpen;
  HWND        myHwnd;
  DM::Vec2i   myLastMousePosition;
};