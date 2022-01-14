#pragma once

typedef union SDL_Event SDL_Event;

namespace yeop::core 
{
  struct ImguiWindowProperties
  {
    bool MoveFromTitleBarOnly = true;
    bool isDockingEnabled = false;
    bool isViewportEnabled = false;
  };

  class ImguiWindow
  {
    public:
      ImguiWindow() {};
      ~ImguiWindow() {};

      void Create(const ImguiWindowProperties& props);
      void Clean();

      void HandleSDLEvent(SDL_Event& event);

      bool WantCaptureMouse();
      bool WantCaptureKeyboard();

      void StartRender();
      void EndRender();
  };
}