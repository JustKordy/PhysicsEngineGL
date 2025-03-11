#include "UI.h"



typedef struct User
{
    const char *name;
} User;

UI::UI(GLFWwindow *window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
 
}

UI::~UI()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}


void UI::Update()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::SetWindowPos({0, 0});
    ImGui::SetWindowSize({100, 960});

    this->DrawUI();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    
}

float col[3];
void UI::DrawUI()
{
    ImGui::Begin("Window");
    ImGui::SeparatorText("Add cube section");
    ImGui::ColorEdit3("Pick color", col);
    if(ImGui::Button("Add Cube")){
        if(OnAddCube)
        {
            OnAddCube();
        }
    }
    ImGui::End();
}
