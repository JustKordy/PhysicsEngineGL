#pragma once
#include <glm/glm.hpp>
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
#include <functional>
#include <GLFW/glfw3.h>
#include "../Renderable/Renderable.h"
#include <vector>

class UI
{

public:
    UI(GLFWwindow* window);
    ~UI();

    void Update();

    struct CubeOptions{
        glm::vec4 color;
        glm::vec3 position;
        float scale;
        float mass;
    };

    std::function<void(CubeOptions)> OnAddCube;
    std::function<void(int)> OnDestroyObject;
   
    std::vector<Renderable*>* m_RenderableObjects;
private:
    void DrawUI();


};  