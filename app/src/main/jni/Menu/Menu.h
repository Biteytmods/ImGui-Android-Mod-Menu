#ifndef MENU
#define MENU
#include "ImGui/imgui.h"
using namespace ImGui;
namespace Menu
{
  struct {
        
      bool BoolExample = false;
      bool FloatExample = false;
      bool IntExample = false;
      bool VoidExample = false;
    
    } SWITCH; //you can write whatever you want and use SWITCH.BoolExample

    
    int (*Screen_get_width)();
    int (*Screen_get_height)();
    ImVec4 color = ImVec4(1, 1, 1, 1);
    
    bool* p_open; //to open menu bars
    
    void DrawMenu() /*main menu function*/
    {
        
        static bool show_demo_window = false;
        static bool show_another_window = false;
        static bool show_app_metrics = false;
        static bool showfrm = false;
        static bool show_app_style_editor = false;
        static bool show_app_about = false;
        static bool showtabmenu = false;

        static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

       
       bool FeatureH;
       
       if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);
            
        // Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            static float f = 0.0f;
            static int counter = 0;
            
            ImGui::SetNextWindowSize(ImVec2(400, 450), ImGuiCond_FirstUseEver); //Set Initial menu size
            ImGui::Begin("Hello, World!", p_open, ImGuiWindowFlags_MenuBar); // Create a window called "Hello, world!" and append into it.
            
          if (ImGui::BeginMenuBar())
           {
             if (ImGui::BeginMenu("Mod Tools"))
              {
                 ImGui::MenuItem("Style Editor", NULL, &show_app_style_editor);
                 ImGui::EndMenu();
              }
              ImGui::EndMenuBar();
           }
              if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
               {
               
                 if (ImGui::BeginTabItem("Section 1"))
                  {
                      Checkbox("Bool on", &SWITCH.BoolExample); //you can write this too
                      ImGui::Checkbox("Set 100", &SWITCH.FloatExample);
                      Checkbox("int", &SWITCH.IntExample);
                      ImGui::Checkbox("Void", &SWITCH.VoidExample);
                     ImGui::EndTabItem();
                  }
                  if (ImGui::BeginTabItem("Section 2"))
                   {
                      ImGui::Text("Lorem ipsum is a dummy text");               // Display some text (you can use a format strings too)
                      ImGui::Checkbox("FrameRate Viewer", &showfrm);
                      ImGui::Checkbox("Demo and Settings Panel", &show_demo_window);      // Edit bools storing our window open/close state
                      ImGui::Text("Does Nothing But Looks Cool");
                      ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
                      ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
                      ImGui::Text("Button Tap Counter");
                      if (ImGui::Button("Button"))                            // Buttons return true when clicked, Value increment
                          counter++;
                         ImGui::SameLine();
                         ImGui::Text("counter = %d", counter);
                      ImGui::EndTabItem();
                   }
                    ImGui::EndTabBar();
               }
               
      if (show_app_style_editor)
       {
          ImGui::Begin("Mod Menu Style Editor", &show_app_style_editor);
          ImGui::ShowStyleEditor();
          ImGui::End();
       }
       
     if (showfrm)
     {
          int corner = 0;
    ImGuiIO& io = ImGui::GetIO();
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
    if (corner != -1)
    {
        const float PAD = 10.0f;
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImVec2 work_pos = viewport->WorkPos; // Use work area to avoid menu-bar/task-bar, if any!
        ImVec2 work_size = viewport->WorkSize;
        ImVec2 window_pos, window_pos_pivot;
        window_pos.x = (corner & 1) ? (work_pos.x + work_size.x - PAD) : (work_pos.x + PAD);
        window_pos.y = (corner & 2) ? (work_pos.y + work_size.y - PAD) : (work_pos.y + PAD);
        window_pos_pivot.x = (corner & 1) ? 1.0f : 0.0f;
        window_pos_pivot.y = (corner & 2) ? 1.0f : 0.0f;
        ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
        window_flags |= ImGuiWindowFlags_NoMove;
    }
    ImGui::SetNextWindowBgAlpha(0.40f); // Transparent background
    if (ImGui::Begin("Framrate overlay", p_open, window_flags))
    {
        
        ImGui::Text("           FrameRate");
        ImGui::Separator();
        ImGui::Text("App Average %.3f ms\n""     Frames %.1f FPS", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::SameLine();
    
        if (ImGui::BeginPopupContextWindow())
        {
            if (ImGui::MenuItem("Custom",       NULL, corner == -1)) corner = -1;
            if (ImGui::MenuItem("Top-left",     NULL, corner == 0)) corner = 0;
            if (ImGui::MenuItem("Top-right",    NULL, corner == 1)) corner = 1;
            if (ImGui::MenuItem("Bottom-left",  NULL, corner == 2)) corner = 2;
            if (ImGui::MenuItem("Bottom-right", NULL, corner == 3)) corner = 3;
            if (p_open && ImGui::MenuItem("Close")) *p_open = false;
            ImGui::EndPopup();
        }
    }
    ImGui::End();
     }
       
     if (show_another_window)
      {
        ImGui::Begin("Viewer", &show_another_window /*p_open*/, ImGuiWindowFlags_MenuBar);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
                if (ImGui::BeginMenuBar())
         {
        //if (ImGui::MenuItem("MenuItem")) {} // You can also use MenuItem() inside a menu bar!
           if (ImGui::BeginMenu("Tools"))
            {
               ImGui::MenuItem("Style Editor", NULL, &show_app_style_editor);
               ImGui::MenuItem("About Dear ImGui", NULL, &show_app_about);
               ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
         }
            ImGui::Text("Hello from another window!");
            ImGui::Text("App Average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

            if (ImGui::Button("Close")) show_another_window = false;
            ImGui::End();
       }
            ImGui::TextWrapped("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }
    }
 void DrawImGuiMenu()
    {
        if (init && Screen_get_height)
        {
            ImGuiIO &io = ImGui::GetIO();
            static bool WantTextInputLast = false;
            if (io.WantTextInput && !WantTextInputLast)
                displayKeyboard(true);
            WantTextInputLast = io.WantTextInput;
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplAndroid_NewFrame(Screen_get_width(), Screen_get_height());;
            ImGui::NewFrame();
            DrawMenu();
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            io.KeysDown[io.KeyMap[ImGuiKey_UpArrow]] = false;
            io.KeysDown[io.KeyMap[ImGuiKey_DownArrow]] = false;
            io.KeysDown[io.KeyMap[ImGuiKey_LeftArrow]] = false;
            io.KeysDown[io.KeyMap[ImGuiKey_RightArrow]] = false;
            io.KeysDown[io.KeyMap[ImGuiKey_Tab]] = false;
            io.KeysDown[io.KeyMap[ImGuiKey_Enter]] = false;
            io.KeysDown[io.KeyMap[ImGuiKey_Backspace]] = false;
            io.KeysDown[io.KeyMap[ImGuiKey_PageUp]] = false;
            io.KeysDown[io.KeyMap[ImGuiKey_PageDown]] = false;
            io.KeysDown[io.KeyMap[ImGuiKey_Escape]] = false;
            io.KeysDown[io.KeyMap[ImGuiKey_Delete]] = false;
            io.KeysDown[io.KeyMap[ImGuiKey_Home]] = false;
            io.KeysDown[io.KeyMap[ImGuiKey_End]] = false;
            io.KeysDown[io.KeyMap[ImGuiKey_Insert]] = false;
            ImGui::EndFrame();
        }
    }
    
}


#endif MENU
