#pragma once
#include <vector>
#include <type_traits>
#include "../Renderable/Renderable.h"
#include "../Camera/Camera.h"
#include "../UI/UI.h"

class GLFWwindow;

class Scene{
public:
    Scene();
    ~Scene();

    template<typename T>
    void AddRenderableObject(T* object)
    {
        this->m_RenderableObjects.push_back(object);
        
    }

    void SetUI(UI* ui);

    static void OnScroll(GLFWwindow *window, double xoffset, double yoffset);
    static void OnClick(GLFWwindow* window, int button, int action, int mods);
    static void OnMouseMove(GLFWwindow *window, double xposIn, double yposIn);


    UI* GetUI();
 
    void Update();

    const std::vector<Renderable*>& GetRenderableObjects();

   
    static Camera* m_Camera;

private:
    std::vector<Renderable*> m_RenderableObjects;
    UI* m_UI;

};