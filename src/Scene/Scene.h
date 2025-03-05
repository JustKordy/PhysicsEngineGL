#pragma once
#include <vector>
#include "../Renderable/Renderable.h"
#include "../Camera/Camera.h"

class Scene{
public:
    Scene();
    ~Scene();

    void AddRenderableObject();
    void Update();

    const std::vector<Renderable*>& GetRenderableObjects();

   
    static Camera* m_Camera;

private:
    std::vector<Renderable*> m_RenderableObjects;
};