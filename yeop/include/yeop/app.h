#pragma once

namespace yeop
{
  class App
  {
    public:
      App() {}
      ~App() {}

      virtual void Init() {}
      virtual void Clean() {}

      virtual void Update() {}
      virtual void Render() {}
    private:

  };
}