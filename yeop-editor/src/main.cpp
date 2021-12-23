#include <iostream>
#include "yeop/engine.h"

int main()
{
  yeop::Engine& engine = yeop::Engine::Instance();
  engine.Run();

  return 0;
}