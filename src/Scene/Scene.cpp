#include "Scene.h"
#include "../Utils/Utils.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::SetUI(UI *ui)
{
    this->m_UI = ui;
}

void Scene::OnScroll(GLFWwindow *window, double xoffset, double yoffset)
{
  
    Scene::m_Camera->HandleZoom(yoffset);
}

void Scene::OnClick(GLFWwindow *window, int button, int action, int mods)
{
  

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        Utils::SetMouseClicked(true);
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
        Utils::SetMouseClicked(false);
}

void Scene::OnMouseMove(GLFWwindow *window, double xposIn, double yposIn)
{
    
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
