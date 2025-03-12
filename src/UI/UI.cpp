#include "UI.h"
#include "../Utils/Utils.h"
#include <glm/gtc/type_ptr.hpp>

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
    
    this->DrawUI();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::DrawUI()
{
    ImGui::SetNextWindowPos(ImVec2(0, 0));   
    ImGui::SetNextWindowSize(ImVec2(300, 1280));  


    static CubeOptions options = {
        glm::vec4(1.f),
        glm::vec3(0.f),
        1
    };

    static int first = 0;
    static const char* arr[10];

    ImGui::Begin("Window");
    ImGui::SeparatorText("General");
    ImGui::SeparatorText("Add cube section");
    ImGui::ColorEdit4("Color", glm::value_ptr(options.color));
    ImGui::SliderFloat3("Position", glm::value_ptr(options.position), -10.f, 10.f);
    ImGui::SliderFloat("Scale", &options.scale, 0.f, 10.f);
    if (ImGui::Button("Add Cube"))
    {   
        if (OnAddCube)
        {
            OnAddCube(options);
        }
    }
    ImGui::SeparatorText("Objects");

    if(ImGui::CollapsingHeader("Header")){
        ImGui::Text("Hello mrdko %d", ImGui::IsItemHovered());
    }
    ImGui::ListBox("Objects", &first, arr, IM_ARRAYSIZE(arr));
    ImGui::End();

}
