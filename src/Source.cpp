#include "window/Window.h"

int main()
{
  Window wnd(1280, 720, "aTitle");

  while (wnd.IsOpen())
  {
    wnd.PollEvents();






  }


  return 0;
}