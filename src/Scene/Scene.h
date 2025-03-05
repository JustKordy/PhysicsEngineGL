#pragma once
#include <vector>
#include <type_traits>
#include "../Renderable/Renderable.h"
#include "../Camera/Camera.h"

class Scene{
public:
    Scene();
    ~Scene();

    template<typename T>
    void AddRenderableObject(T* object)
    {
        this->m_RenderableObjects.push_back(object);
        
    }


    void Update();

    const std::vector<Renderable*>& GetRenderableObjects();

   
    static Camera* m_Camera;

private:
    std::vector<Renderable*> m_RenderableObjects;
};