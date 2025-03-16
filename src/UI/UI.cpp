#include "UI.h"
#include "../Utils/Utils.h"
#include <glm/gtc/type_ptr.hpp>
#include "../Scene/Scene.h"
#include "../Logger/Logger.h"
#include "UI.H"

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
    static const char *arr[10];

    ImGui::Begin("Window");
    ImGui::SeparatorText("General");
    if (ImGui::CollapsingHeader("Camera info"))
    {
        // ImGui::Text("Position X: %d Y: %d Z: %d", Scene::m_Camera->GetPosition().x, Scene::m_Camera->GetPosition().y, Scene::m_Camera->GetPosition().z);
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

    if (ImGui::CollapsingHeader("Objects in scene"))
    {
        for (int i = 0; i < m_RenderableObjects->size(); i++)
        {
            ImGui::PushID(i);
            Renderable *obj1 = m_RenderableObjects->at(i);
            if (Cube *obj = dynamic_cast<Cube *>(obj1))
            {
                DrawShapeInfo(Shapes::CubeShape, obj, i);
            }
            else if (Plane *obj = dynamic_cast<Plane *>(obj1))
            {
                DrawShapeInfo(Shapes::PlaneShape, obj, i);
            }
            ImGui::Separator();
            ImGui::PopID();
        }
    }

    ImGui::End();
}

void UI::DrawShapeInfo(Shapes shape, Renderable *obj, int index)
{
    switch (shape)
    {
        case Shapes::CubeShape:
        {

            if (Cube *CubeObj = dynamic_cast<Cube *>(obj))
            {

                Transform *objTr = CubeObj->GetComponent<Transform>();
                RigidBody *objRb = CubeObj->GetComponent<RigidBody>();
                if (!objTr || !objRb)
                {
                    Logger::Error("Couldnt get components");
                    break;
                }
                
                ImGui::Text("Cube %i", index);
                ImGui::Text("X: %f Y: %f Z: %f", objTr->GetPosition().x, objTr->GetPosition().y, objTr->GetPosition().z);
                ImGui::Text("Mass: %f", objRb->GetMass());
                ImGui::Text("Velocity: X:%f Y:%f Z:%f", objRb->GetVelocity().x, objRb->GetVelocity().y, objRb->GetVelocity().z);
                ImGui::Text("Acceleration: X:%f Y:%f Z:%f", objRb->GetAcceleration().x, objRb->GetAcceleration().y, objRb->GetAcceleration().z);
                if (ImGui::Button("Destroy"))
                {
                    if (OnDestroyObject)
                    {
                        OnDestroyObject(index);
                    }
                }
            }
            else
            {
                Logger::Error("Failed to cast to Cube");
            }
            break;
        }

        case Shapes::PlaneShape:
        {
            Plane *PlaneObj = dynamic_cast<Plane *>(obj);
            Transform *objTr = PlaneObj->GetComponent<Transform>();
            RigidBody *objRb = PlaneObj->GetComponent<RigidBody>();
            if (objTr->GetPosition().y <= -100.f)
            {
                OnDestroyObject(index);
            }

            ImGui::Text("Plane %i", index);
            ImGui::Text("X: %f Y: %f Z: %f", objTr->GetPosition().x, objTr->GetPosition().y, objTr->GetPosition().z);
            ImGui::Text("Mass: %f", objRb->GetMass());
            ImGui::Text("Velocity: X:%f Y:%f Z:%f", objRb->GetVelocity().x, objRb->GetVelocity().y, objRb->GetVelocity().z);
            ImGui::Text("Acceleration: X:%f Y:%f Z:%f", objRb->GetAcceleration().x, objRb->GetAcceleration().y, objRb->GetAcceleration().z);
            if (ImGui::Button("Destroy"))
            {
                if (OnDestroyObject)
                {
                    OnDestroyObject(index);
                }
            }
            break;
        }
    }
}
