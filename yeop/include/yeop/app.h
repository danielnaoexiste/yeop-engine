#pragma once

#include "core/window.h"

namespace yeop
{
  class App
  {
    public:
      App() {}
      ~App() {}

      virtual core::WindowProperties GetWindowProperties() { return core::WindowProperties(); }

      virtual void Init() {}
      virtual void Clean() {}

      virtual void Update() {}
      virtual void Render() {}
      virtual void GuiRender() {}
    private:

  };
}