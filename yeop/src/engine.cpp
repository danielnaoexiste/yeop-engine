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
  void Engine::Run(App* app) 
  {
    mLogManager.Init();
    
    YEOP_ASSERT(!mApp, "Attempting to call Engine::Run() when a valid App already exists!");
    if (mApp) return;

    mApp = app;

    if (Init()) 
    {
      while(mIsRunning)
      {
        Update();
        Render();
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

          // Init Input
          input::Mouse::Init();
          input::Keyboard::Init();

          // Init Client
          mApp->Init();
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
    mApp->Clean();

    //managers
    YEOP_ERROR("Yeop cleaned... See you next time!");
    mLogManager.Clean();
		input::Joystick::Clean();

    // Shutdown SDL
    mWindow.Destroy();
    SDL_Quit();
    
    return;
  }

  void Engine::Update()
  {
    mWindow.HandleEvents();
    mApp->Update();
  }

  void Engine::Render()
  {
    mWindow.StartRender();
		mApp->Render();
		mWindow.EndRender();
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
      mIsInitialized(false),
      mApp(nullptr) 
  {}
}