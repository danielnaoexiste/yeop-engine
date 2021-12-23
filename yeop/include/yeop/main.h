
#pragma once

#include "yeop/app.h"
#include "yeop/engine.h"

yeop::App* CreateApp();

int main()
{
	yeop::App* app = CreateApp();
	yeop::Engine::Instance().Run(app);
	delete app;
	return 0;
}