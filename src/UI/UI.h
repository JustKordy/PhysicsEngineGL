#pragma once
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"


class GLFWwindow;

class UI
{
public:
    UI(GLFWwindow* window);
    ~UI();

    void Update();


private:
    void DrawUI();

};  