#pragma once
#include <glm/glm.hpp>
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
#include <functional>
#include <GLFW/glfw3.h>

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
    };

    std::function<void(CubeOptions)> OnAddCube;
private:
    void DrawUI();

};  