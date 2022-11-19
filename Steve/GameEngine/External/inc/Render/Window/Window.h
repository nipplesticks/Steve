#pragma once
#include <Windows.h>
#include <Common/Typedef.h>
#include <Common/DMath.h>
#include <string>

namespace Render
{
  class Window
  {
  public:
    Window(uint16 x, uint16 y, const std::string& title = "aWindow");

    static LRESULT CALLBACK PreWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    bool ProcessEvent(UINT aMessage, WPARAM aWParam, LPARAM aLParam);

    bool IsOpen() const;

    void PollEvents();

    HWND GetHwnd() const;

    DM::Vec2u GetSize() const;
    void      SetMousePosition(const DM::Vec2i& mousePosition);

  private:
    std::string myTitle;
    bool        myIsOpen;
    HWND        myHwnd;
    DM::Vec2i   myLastMousePosition;
  };
} // namespace Render