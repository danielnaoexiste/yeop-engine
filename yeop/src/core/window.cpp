#include "SDL2/SDL.h"

#include "log.h"
#include "engine.h"
#include "core/window.h"
#include "input/mouse.h"
#include "input/keyboard.h"
#include "input/joystick.h"


namespace yeop::core
{
  Window::Window() : mWindow(nullptr), mRenderer(nullptr) {}
  Window::~Window()

  {
    if(mWindow)
    {
      Destroy();
    }
  }

  bool Window::Create()
  {
    mWindow = SDL_CreateWindow("YEOP!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
   
    if (!mWindow) 
    {
      YEOP_FATAL("Window failed to create: {}", SDL_GetError()); 
      return false;
    }

    YEOP_DEBUG("Window created...");
    
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
   
    if (!mRenderer) 
    {
      YEOP_FATAL("Renderer failed to create: {}", SDL_GetError()); 
      return false;
    }
    else
    {
      SDL_SetRenderDrawColor(mRenderer, 40, 45, 52, 255);
      YEOP_DEBUG("Renderer created...");
    }


    return true;
  }

  void Window::HandleEvents() 
  {
    SDL_Event e;
    while(SDL_PollEvent(&e)) 
    {
      switch (e.type)
      {
      case SDL_QUIT:
        Engine::Instance().Quit();
        break;
      
      case SDL_CONTROLLERDEVICEADDED:
        input::Joystick::OnJoystickConnected(e.cdevice);
        break;
      
      case SDL_CONTROLLERDEVICEREMOVED:
        input::Joystick::OnJoystickDisconnected(e.cdevice);
        break;
      
      default:
        break;
      }
    }

    input::Mouse::Update();
    input::Keyboard::Update();
    input::Joystick::Update();
  }

  void Window::StartRender()
  {
    SDL_RenderClear(mRenderer);
  }

  void Window::EndRender()
  {
    SDL_RenderPresent(mRenderer);
  }

  void Window::Destroy()
  {
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    mWindow = nullptr;
    mRenderer = nullptr;
  }
}
