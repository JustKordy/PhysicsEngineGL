#include "Scene.h"
#include "../Utils/Utils.h"
#include "../Components/Transform/Transform.h"
#include "../Components/RigidBody/RigidBody.h"
#include "../Shapes/Cube/Cube.h"
#include "../Memory/Memory.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::SetUI(UI *ui)
{
    this->m_UI = ui;
    m_UI->OnAddCube = [this](UI::CubeOptions options) {this->AddCube(options); };
    m_UI->m_RenderableObjects = &m_RenderableObjects;
    m_UI->OnDestroyObject = [this](int index) { this->DestroyObject(index); };
}

void Scene::OnScroll(GLFWwindow *window, double xoffset, double yoffset)
{
    if (ImGui::GetIO().WantCaptureMouse)
        return;

    Scene::m_Camera->HandleZoom(yoffset);
}

void Scene::OnClick(GLFWwindow *window, int button, int action, int mods)
{
    if (ImGui::GetIO().WantCaptureMouse)
        return;

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        Utils::SetMouseClicked(true);
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
        Utils::SetMouseClicked(false);
}

void Scene::OnMouseMove(GLFWwindow *window, double xposIn, double yposIn)
{
    if (ImGui::GetIO().WantCaptureMouse)
        return;

    Scene::m_Camera->HandleLook(xposIn, yposIn, Utils::isMouseClicked());
}

UI *Scene::GetUI()
{
    return this->m_UI;
}

void Scene::Update()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (int i = 0; i < m_RenderableObjects.size(); i++)
    {
        m_RenderableObjects[i]->Update();
        m_RenderableObjects[i]->Draw();
    }

    this->m_UI->Update();
}

const std::vector<Renderable *> &Scene::GetRenderableObjects()
{
    return this->m_RenderableObjects;
}

// PRIVATE :: ::  : : : :: 

void Scene::AddCube(UI::CubeOptions options)
{
    static Shader cubeShader(Utils::GetResourcePath("/shaders/cube.vert").c_str(), Utils::GetResourcePath("/shaders/cube.frag").c_str());

    Cube* cube = new Cube(cubeShader);
    auto* rb = cube->AddComponent<RigidBody>();
    rb->SetMass(options.mass);
    rb->SetAcceleration(glm::vec3(0.0f, -9.81f, 0.f) / rb->GetMass());
    cube->SetColor(options.color);
    cube->AddComponent<Transform>()->SetPosition(options.position);
    cube->Scale(glm::vec3(options.scale));
    AddRenderableObject(cube);
}

void Scene::DestroyObject(int index)
{
    Memory::Clean(m_RenderableObjects[index]);
    m_RenderableObjects.erase(m_RenderableObjects.begin() + index);
}
