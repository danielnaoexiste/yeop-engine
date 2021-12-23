#include "log.h"
#include "input/keyboard.h"

#include <algorithm>

#include "SDL2/SDL_keyboard.h"

namespace yeop::input
{
  std::array<bool, Keyboard::KeyCount> Keyboard::keys;
  std::array<bool, Keyboard::KeyCount> Keyboard::keysLast;

  void Keyboard::Init()
  {
    std::fill(keys.begin(), keys.end(), false);
    std::fill(keysLast.begin(), keysLast.end(), false);
  }

  void Keyboard::Update()
  {
    memcpy(&keysLast, &keys, sizeof(keys));
    const Uint8* state = SDL_GetKeyboardState(nullptr);

    for (int i = YEOP_INPUT_KEY_FIRST; i < KeyCount; i++)
    {
      keys[i] = state[i];
    }
  }

  bool Keyboard::Key(int key) 
  {
    YEOP_ASSERT(key >= YEOP_INPUT_KEY_FIRST && key <= KeyCount, "Invalid keyboard key!");

    if (key >= YEOP_INPUT_KEY_FIRST && key <= KeyCount)
    {
      return keys[key];
    }
    
    return false;
  }
 
  bool Keyboard::KeyUp(int key) 
  {
    YEOP_ASSERT(key >= YEOP_INPUT_KEY_FIRST && key <= KeyCount, "Invalid keyboard Key!");

    if (key >= YEOP_INPUT_KEY_FIRST && key <= KeyCount)
    {
      return keys[key] && keysLast[key];
    }

    return false;
  }
 
  bool Keyboard::KeyDown(int key) 
  {
    YEOP_ASSERT(key >= YEOP_INPUT_KEY_FIRST && key <= KeyCount, "Invalid keyboard key!");

    if (key >= YEOP_INPUT_KEY_FIRST && key <= KeyCount)
    {
      return keys[key] && !keysLast[key];
    }

    return false;
  }
}