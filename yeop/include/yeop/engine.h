#pragma once

#include "core/window.h"
#include "managers/logmanager.h"

namespace yeop
{
  class Engine
  {
    public:
      ~Engine() {};
      static Engine& Instance();
      
      void Run();
      inline void Quit() { mIsRunning = false; }

    private:
      void GetInfo();
      bool Init();
      void Clean();

    private:
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