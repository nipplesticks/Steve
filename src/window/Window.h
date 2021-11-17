#pragma once
#include <Windows.h>
#include "../utility/Vector2u.h"
#include <string>

class Window
{
public:
  Window(uint x, uint y, const std::string & title = "");
  ~Window();

  bool ProcessEvent(UINT aMessage, WPARAM aWParam, LPARAM aLParam);
  bool IsOpen() const;

  void PollEvents();
  HWND GetHwnd() const;

  void SetFullscreen(bool isFullscreen);
  Vector2u GetSize() const;

public:
  static LRESULT CALLBACK PreWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
  std::string myTitle;
  bool myIsOpen;
  HWND myHwnd;



};