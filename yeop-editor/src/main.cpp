#include <iostream>
#include "yeop/log.h"
#include "yeop/app.h"
#include "yeop/main.h"
#include "yeop/engine.h"

#include "yeop/input/mouse.h"
#include "yeop/input/keyboard.h"
#include "yeop/input/joystick.h"

using namespace yeop;
class Editor : public App
{
  public:
    void Init() override
    {
      YEOP_TRACE("Editor::Init();")
    }

    void Clean() override
    {
      YEOP_TRACE("Editor::Clean();")
    }

    void Update() override
    {
      YEOP_TRACE("Editor::Update();")
      // input::MOUSE debug position and clicks
      // YEOP_TRACE("X: {} Y: {}, {}{}{}", input::Mouse::X(), input::Mouse::Y(), 
      //   input::Mouse::Button(YEOP_INPUT_MOUSE_LEFT), 
      //   input::Mouse::Button(YEOP_INPUT_MOUSE_MIDDLE), 
      //   input::Mouse::Button(YEOP_INPUT_MOUSE_RIGHT));

      // keyboard::Key debug
      if (input::Keyboard::Key(YEOP_INPUT_KEY_R))
      {
        YEOP_TRACE("Button Pressed: {}", "R");
      }
    }

    void Render() override
    {
      YEOP_TRACE("Editor::Render();")
    }

  private:

};

App* CreateApp()
{
  return new Editor();
}