#include <iostream>
#include "yeop/log.h"
#include "yeop/app.h"
#include "yeop/main.h"
#include "yeop/engine.h"

#include "yeop/input/mouse.h"
#include "yeop/input/keyboard.h"
#include "yeop/input/joystick.h"

#include "external/imgui/imgui.h"

using namespace yeop;
class Editor : public App
{
  public:
    core::WindowProperties GetWindowProperties() 
    {
      core::WindowProperties props;
      props.title = "Yeop Game Editor";
      props.imguiProps.isViewportEnabled = true;
      return props;
    }

    void Init() override
    {
      YEOP_TRACE("Editor::Init();")
    }

    void Clean() override
    {
      YEOP_TRACE("Editor::Clean();")
    }

    void Update() override
    {

    }

    void Render() override
    {

    }

    void GuiRender() override 
    {
      if(ImGui::Begin("Inspector"))
      {
        ImGui::Text("Transform");
        ImGui::DragInt2("Position", &xPos);
        ImGui::DragInt2("Scale", &xScale, 1, 0, 10);
      }
      ImGui::End();
    }

  private:
    int xPos, yPos = 0;
    int xScale, yScale = 0;
};

App* CreateApp()
{
  return new Editor();
}