#include "Scene.h"


Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::AddRenderableObject()
{
}

void Scene::Update()
{
    for(int i = 0; i < m_RenderableObjects.size(); i++)
    {
        m_RenderableObjects[i]->Update();
        m_RenderableObjects[i]->Draw();
    }
}

const std::vector<Renderable *> &Scene::GetRenderableObjects()
{
    return this->m_RenderableObjects;
}

