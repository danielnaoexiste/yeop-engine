#include "input/mouse.h"
#include "log.h"

#include <algorithm>

#include "SDL/SDL_mouse.h"

namespace yeop::input
{
  int Mouse::x = 0;
  int Mouse::xLast = 0;
  int Mouse::y = 0;
  int Mouse::yLast = 0;

  std::array<bool, Mouse::ButtonCount> Mouse::buttons;
  std::array<bool, Mouse::ButtonCount> Mouse::buttonsLast;

  void Mouse::Init()
  {
    std::fill(buttons.begin(), buttons.end(), false);
    std::fill(buttonsLast.begin(), buttonsLast.end(), false);
  }

  void Mouse::Update()
  {
    xLast = x;
    yLast = y;

    memcpy(&buttonsLast, &buttons, sizeof(buttons));

    Uint32 state = SDL_GetMouseState(&x, &y);

    for (int i = 0; i < ButtonCount; i++)
    {
      buttons[i] = state & SDL_BUTTON(i + 1);
    }
  }

  bool Mouse::Button(int button) 
  {
    YEOP_ASSERT(button >= YEOP_INPUT_MOUSE_FIRST && button <= YEOP_INPUT_MOUSE_LAST, "Invalid mouse button!");

    if (button >= YEOP_INPUT_MOUSE_FIRST && button <= YEOP_INPUT_MOUSE_LAST)
    {
      return buttons[button - 1];
    }

    return false;
  }
 
  bool Mouse::ButtonUp(int button) 
  {
    YEOP_ASSERT(button >= YEOP_INPUT_MOUSE_FIRST && button <= YEOP_INPUT_MOUSE_LAST, "Invalid mouse button!");

    if (button >= YEOP_INPUT_MOUSE_FIRST && button <= YEOP_INPUT_MOUSE_LAST)
    {
      return buttons[button - 1] && buttonsLast[button - 1];
    }

    return false;
  }
 
  bool Mouse::ButtonDown(int button) 
  {
    YEOP_ASSERT(button >= YEOP_INPUT_MOUSE_FIRST && button <= YEOP_INPUT_MOUSE_LAST, "Invalid mouse button!");

    if (button >= YEOP_INPUT_MOUSE_FIRST && button <= YEOP_INPUT_MOUSE_LAST)
    {
      return buttons[button - 1] && !buttonsLast[button - 1];
    }

    return false;
  }
}