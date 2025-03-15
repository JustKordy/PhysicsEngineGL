#pragma once
#include <glm/glm.hpp>
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
#include <functional>
#include <GLFW/glfw3.h>
#include "../Renderable/Renderable.h"
#include "../Components/Transform/Transform.h"
#include "../Components/RigidBody/RigidBody.h"
#include "../Renderable/Renderable.h"
#include "../Shapes/Cube/Cube.h"
#include "../Plane/Plane.h"
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
    enum Shapes {
        CubeShape = 0,
        PlaneShape = 1,
    };

    void DrawUI();

    
    void DrawShapeInfo(Shapes shape, Renderable* obj, int index);


};  