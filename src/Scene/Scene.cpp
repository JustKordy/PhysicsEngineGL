#include "Scene.h"


Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::Update()
{   
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


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

