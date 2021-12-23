#pragma once

namespace yeop::managers
{
  class LogManager
  {
    public:
      LogManager() = default;
      ~LogManager() = default;

      void Init();
      void Clean();
  };
} 
