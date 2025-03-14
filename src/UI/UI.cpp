#include "UI.h"
#include "../Utils/Utils.h"
#include <glm/gtc/type_ptr.hpp>
#include "../Scene/Scene.h"
#include "../Logger/Logger.h"
#include "../Shapes/Cube/Cube.h"
#include "../Components/Transform/Transform.h"
#include "../Components/RigidBody/RigidBody.h"

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
        1,
        1
    };

    static int first = 0;
    static const char* arr[10];

    ImGui::Begin("Window");
    ImGui::SeparatorText("General");
    if(ImGui::CollapsingHeader("Camera info")){
        //ImGui::Text("Position X: %d Y: %d Z: %d", Scene::m_Camera->GetPosition().x, Scene::m_Camera->GetPosition().y, Scene::m_Camera->GetPosition().z);
    }
    ImGui::SeparatorText("Add cube section");
    ImGui::ColorEdit4("Color", glm::value_ptr(options.color));
    ImGui::SliderFloat3("Position", glm::value_ptr(options.position), -10.f, 10.f);
    ImGui::SliderFloat("Scale", &options.scale, 0.f, 10.f);
    ImGui::SliderFloat("Mass", &options.mass, 0.1f, 100.f);
    if (ImGui::Button("Add Cube"))
    {   
        if (OnAddCube)
        {
            OnAddCube(options);
        }
    }
    ImGui::SeparatorText("Objects");

    if(ImGui::CollapsingHeader("Header")){
        for(int i = 0; i < m_RenderableObjects->size(); i++){
            ImGui::PushID(i);
            Renderable* obj1 = m_RenderableObjects->at(i);
            if(auto * obj = dynamic_cast<Cube*>(obj1))
            {
                auto* objTr = obj->GetComponent<Transform>();
                auto* objRb = obj->GetComponent<RigidBody>();

                ImGui::Text("Cube %i", i);
                ImGui::Text("X: %f Y: %f Z: %f", objTr->GetPosition().x,objTr->GetPosition().y,objTr->GetPosition().z);
                ImGui::Text("Mass: %f", obj->GetComponent<RigidBody>()->GetMass());
                ImGui::Text("Velocity: X:%f Y:%f Z:%f", objRb->GetVelocity().x, objRb->GetVelocity().y, objRb->GetVelocity().z);
                ImGui::Text("Acceleration: X:%f Y:%f Z:%f", objRb->GetAcceleration().x, objRb->GetAcceleration().y, objRb->GetAcceleration().z);
                if(ImGui::Button("Destroy")){
                    if(OnDestroyObject){
                        OnDestroyObject(i);
                    }
                }
            }
            ImGui::Separator();
            ImGui::PopID();
        }
    }
    
    ImGui::End();

}
