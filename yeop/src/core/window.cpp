#include "SDL2/SDL.h"
#include "glad/glad.h"

#include "log.h"
#include "engine.h"

#include "core/window.h"
#include "input/mouse.h"
#include "input/keyboard.h"
#include "input/joystick.h"

namespace yeop::core
{
  WindowProperties::WindowProperties()
	{
		title = "Yeop Engine";
		x = SDL_WINDOWPOS_CENTERED;
		y = SDL_WINDOWPOS_CENTERED;
		w = 1280;
		h = 720;
		wMin = 320;
		hMin = 180;
		flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
		colorRed = static_cast<float>(0x40) / static_cast<float>(0xFF);
		colorGreen = static_cast<float>(0x45) / static_cast<float>(0xFF);
		colorBlue =	static_cast<float>(0x52) / static_cast<float>(0xFF);
	}

  

  Window::Window() : mWindow(nullptr) {}
  Window::~Window()

  {
    if(mWindow)
    {
      Destroy();
    }
  }

  bool Window::Create(const WindowProperties& props)
  {
    YEOP_INFO("title: {}\n\tx: {}/{}\n\ty: {}/{}\n\tw: {}\n\th: {}\n\tf: {}",
    props.title.c_str(), props.x, SDL_WINDOWPOS_CENTERED, props.y, SDL_WINDOWPOS_CENTERED, props.w, props.h, props.flags);
    mWindow = SDL_CreateWindow(props.title.c_str(), props.x, props.y, props.w, props.h, props.flags);
   
    if (!mWindow) 
    {
      YEOP_FATAL("Window failed to create: {}", SDL_GetError()); 
      return false;
    }

    YEOP_DEBUG("Window created...");
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_SetWindowMinimumSize(mWindow, props.wMin, props.hMin);

    mGLContext = SDL_GL_CreateContext(mWindow);
    if (mGLContext == nullptr)
		{
			YEOP_FATAL("Error creating OpenGL context: {}", SDL_GetError());
			return false;
		}

		gladLoadGLLoader(SDL_GL_GetProcAddress);
    YEOP_DEBUG("OpenGL Context created...");

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(props.colorRed, props.colorGreen, props.colorBlue, 1);
    
    mImguiWindow.Create(props.imguiProps);

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

    // Update Input
    if(!mImguiWindow.WantCaptureMouse()) { input::Mouse::Update(); }
    if(!mImguiWindow.WantCaptureKeyboard()) { input::Keyboard::Update(); }
    input::Joystick::Update();
  }

  void Window::StartRender()
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  void Window::EndRender()
  {
    mImguiWindow.StartRender();
    Engine::Instance().GetApp().GuiRender();
    mImguiWindow.EndRender();
    
    SDL_GL_SwapWindow(mWindow);
  }

  void Window::Destroy()
  {
    SDL_DestroyWindow(mWindow);
    SDL_GL_DeleteContext(mGLContext);  
    mWindow = nullptr;
  }
}
