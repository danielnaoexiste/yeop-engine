#pragma once

#include <string>
#include "imguiwindow.h"

struct SDL_Window;
using SDL_GLContext = void*;
namespace yeop::core
{
  struct WindowProperties
  {
    std::string title;
    int x, y, w, h;
    int wMin, hMin;
    int flags;
    float colorRed, colorGreen, colorBlue;
    ImguiWindowProperties imguiProps;

    WindowProperties();
  };

  class Window 
  {
    public:
      Window();
      ~Window();

      bool Create(const WindowProperties& props);
      void Destroy();

      void HandleEvents();

      inline SDL_Window* GetSDLWindow() { return mWindow; }
      inline SDL_GLContext GetSDLContext() { return mGLContext; }

      void StartRender();
      void EndRender();

    private:
      WindowProperties mWindowProperties;
      SDL_Window* mWindow;
      SDL_GLContext mGLContext;
      ImguiWindow mImguiWindow;
  };
}