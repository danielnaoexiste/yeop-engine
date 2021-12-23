#pragma once

#include "app.h"
#include "core/window.h"
#include "managers/logmanager.h"

namespace yeop
{
  class App;
  class Engine
  {
    public:
      ~Engine() {};
      static Engine& Instance();
      
      void Run(App* app);
      inline void Quit() { mIsRunning = false; }

    private:
      void GetInfo();
      bool Init();
      void Update();
      void Render();
      void Clean();

    private:
      App* mApp;
      bool mIsRunning;
      bool mIsInitialized;
      core::Window mWindow;

      //Managers
      managers::LogManager mLogManager;

      // Singleton
      Engine();
      static Engine* mInstance;
      
  };

}