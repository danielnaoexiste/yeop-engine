#include "core/imguiwindow.h"
#include "engine.h"

#include "SDL2/SDL.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"


namespace yeop::core
{
  void ImguiWindow::Create(const ImguiWindowProperties& props)
  {
    IMGUI_CHECKVERSION();

    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();

    io.ConfigWindowsMoveFromTitleBarOnly = props.MoveFromTitleBarOnly; 
    if (props.isDockingEnabled) { io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; }
    if (props.isViewportEnabled) { io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; }
    
    auto& window = Engine::Instance().GetWindow();
    ImGui_ImplSDL2_InitForOpenGL(window.GetSDLWindow(), window.GetSDLContext());
    ImGui_ImplOpenGL3_Init();
  }

  void ImguiWindow::Clean()
  {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
  }

  void ImguiWindow::HandleSDLEvent(SDL_Event& event)
  {
    ImGui_ImplSDL2_ProcessEvent(&event);
  }

  void ImguiWindow::StartRender()
  {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(Engine::Instance().GetWindow().GetSDLWindow());
    ImGui::NewFrame();
  }

  void ImguiWindow::EndRender()
  {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) 
    { 
      auto& window = Engine::Instance().GetWindow();
      ImGui::UpdatePlatformWindows();
      ImGui::RenderPlatformWindowsDefault();
      SDL_GL_MakeCurrent(window.GetSDLWindow(), window.GetSDLContext());
    }
  }

  bool ImguiWindow::WantCaptureMouse()
  {
    return ImGui::GetIO().WantCaptureMouse;
  }

  bool ImguiWindow::WantCaptureKeyboard()
  {
    return ImGui::GetIO().WantCaptureKeyboard;
  }
}