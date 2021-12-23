#include "SDL2/SDL.h"

#include "input/keyboard.h"
#include "input/joystick.h"
#include "input/mouse.h"
#include "engine.h"
#include "log.h"

namespace yeop 
{
  // public
  Engine& Engine::Instance()
  {
    if (!mInstance)
    {
      mInstance = new Engine();
    }

    return *mInstance;
  }


  // private
  void Engine::Run() 
  {
    if (Init()) 
    {
      while(mIsRunning)
      {
        mWindow.HandleEvents();

        // input::MOUSE debug position and clicks
        // YEOP_TRACE("X: {} Y: {}, {}{}{}", input::Mouse::X(), input::Mouse::Y(), 
        //   input::Mouse::Button(YEOP_INPUT_MOUSE_LEFT), 
        //   input::Mouse::Button(YEOP_INPUT_MOUSE_MIDDLE), 
        //   input::Mouse::Button(YEOP_INPUT_MOUSE_RIGHT));

        // keyboard::Key debug
        // if (input::Keyboard::Key(YEOP_INPUT_KEY_R))
        // {
        //   YEOP_TRACE("Button Pressed: {}", "R");
        // }

        mWindow.StartRender();
        mWindow.EndRender();
      }

      Clean();
    }
  }

  bool Engine::Init()
  {
    bool ret = false;
    YEOP_ASSERT(!mIsInitialized, "Attempting to call Engine::Init() more than once!")

    if (!mIsInitialized)
    {
      mLogManager.Init();
      
      GetInfo();
      
      if(SDL_Init(SDL_INIT_EVERYTHING) < 0) 
      {
        YEOP_ERROR("SDL failed to init: {}", SDL_GetError()); 
      } 
      else 
      {
        SDL_version version;
        SDL_VERSION(&version);
        YEOP_INFO("Initialized: SDL {}.{}.{}", (int32_t) version.major, (int32_t) version.minor, (int32_t) version.patch);

        if(mWindow.Create())
        {
          ret = true;
          mIsRunning = true;
          mIsInitialized= true;

          // Initialize Input
          input::Mouse::Init();
          input::Keyboard::Init();
        } 
      }
    }

    if (!ret)
    {
      YEOP_ERROR("Engine failed to init. Cleaning up..."); 
      Clean();
    }

    return ret;
  }

  void Engine::Clean() 
  {
    mIsRunning = false;
    mIsInitialized = false;
    
    //managers
    YEOP_ERROR("Yeop cleaned... See you next time!");
    mLogManager.Clean();
		input::Joystick::Clean();

    // Shutdown SDL
    mWindow.Destroy();
    SDL_Quit();
    
    return;
  }
  
  void Engine::GetInfo() 
  {    
    YEOP_DEBUG("YEOP Engine v{}.{}", "0", "1");

    #ifdef YEOP_CONFIG_DEBUG
      YEOP_INFO("Configuration: DEBUG");
    #endif

    #ifdef YEOP_CONFIG_RELEASE
     YEOP_INFO("Configuration: RELEASE");
    #endif

    #ifdef YEOP_PLATFORM_WINDOWS
     YEOP_INFO("Platform: WINDOWS");
    #endif
    
    #ifdef YEOP_PLATFORM_MACOSX
     YEOP_INFO("Platform: MACOSX");
    #endif
    
    #ifdef YEOP_PLATFORM_LINUX
     YEOP_INFO("Platform: LINUX");
    #endif

    return;
  }

  Engine* Engine::mInstance = nullptr;

  Engine::Engine() 
    : mIsRunning(false),
    mIsInitialized(false) 
  {}
}