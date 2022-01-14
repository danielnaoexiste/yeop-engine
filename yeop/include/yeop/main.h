
#pragma once

#include "app.h"
#include "engine.h"

yeop::App* CreateApp();

int main()
{
	yeop::App* app = CreateApp();
	yeop::Engine::Instance().Run(app);
	delete app;
	return 0;
}