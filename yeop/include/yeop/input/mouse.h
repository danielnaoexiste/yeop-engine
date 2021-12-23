#pragma once

#include <array>

// Adapted from progrematic/hippo.git
namespace yeop::input
{
  class Mouse 
  {
    public:
      static void Init();
      static void Update();

      inline static int X() { return x; }
      inline static int Y() { return y; }

      inline static int DeltaX() { return x - xLast; }
      inline static int DeltaY() { return y - yLast; }

      static bool Button(int button);
      static bool ButtonUp(int button);
      static bool ButtonDown(int button);

    private:
      // SDL Supports up to 5 mouse buttons
      constexpr static const int ButtonCount = 5;
      static int x, xLast;
      static int y, yLast;  

      static std::array<bool, ButtonCount> buttons;
      static std::array<bool, ButtonCount> buttonsLast;
  };
}

// Adapted from SDL - See SDL_BUTTON_LEFT
enum
{
  YEOP_INPUT_MOUSE_FIRST = 1,
  YEOP_INPUT_MOUSE_LEFT = YEOP_INPUT_MOUSE_FIRST,
  YEOP_INPUT_MOUSE_MIDDLE = 2,
  YEOP_INPUT_MOUSE_RIGHT = 3,
  YEOP_INPUT_MOUSE_X1 = 4,
  YEOP_INPUT_MOUSE_X2 = 5,
  YEOP_INPUT_MOUSE_LAST = 5
};