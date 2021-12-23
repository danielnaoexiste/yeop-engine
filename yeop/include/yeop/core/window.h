#pragma once

struct SDL_Window;
using SDL_GLContext = void*;
namespace yeop::core
{
  class Window 
  {
    public:
      Window();
      ~Window();

      bool Create();
      void Destroy();

      void HandleEvents();

      void StartRender();
      void EndRender();

    private:
      SDL_Window* mWindow;
      SDL_Renderer* mRenderer;
      SDL_GLContext mGLContext;
  };
}