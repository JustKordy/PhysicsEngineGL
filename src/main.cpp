
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include "Utils/Utils.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "Logger/Logger.h"
#include "Shader/Shader.h"
#include "Camera/Camera.h"
#include "UI/UI.h"
#include "Components/RigidBody/RigidBody.h"
#include "Components/Transform/Transform.h"
#include "Shapes/Cube/Cube.h"
#include "Renderer/Renderer.h"
#include "Plane/Plane.h"
#include "Scene/Scene.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

float deltaTime = 0.0f;
float lastFrame = 0.0f;

Camera *Scene::m_Camera = new Camera();
int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Physics engine", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glewExperimental = GL_FALSE;
    glewInit();

    int viewportWidth, viewportHeight;
    glfwGetFramebufferSize(window, &viewportWidth, &viewportHeight);
    glViewport(0, 0, viewportWidth, viewportHeight);

    glEnable(GL_DEPTH_TEST);

    Scene* scene = new Scene();

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, scene->OnMouseMove);
    glfwSetScrollCallback(window, scene->OnScroll);
    glfwSetMouseButtonCallback(window, scene->OnClick);

    Shader cubeShader(Utils::GetResourcePath("/shaders/cube.vert").c_str(), Utils::GetResourcePath("/shaders/cube.frag").c_str());
    Shader planeShader(Utils::GetResourcePath("/shaders/plane.vert").c_str(), Utils::GetResourcePath("/shaders/plane.frag").c_str());

    Cube *cube = new Cube(cubeShader);
    Plane *plane = new Plane(planeShader);
    UI *ui = new UI(window);

    cube->Scale(glm::vec3(1.f));
    cube->AddComponent<RigidBody>();
    cube->AddComponent<Transform>();

    plane->AddComponent<Transform>(glm::vec3(0.f, -3.f, -5.f));
    plane->AddComponent<RigidBody>();
    plane->SetTexture("transBack.png");

    scene->AddRenderableObject(cube);
    scene->AddRenderableObject(plane);
    scene->SetUI(ui);

    while (!glfwWindowShouldClose(window))
    {

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        Utils::SetDeltaTime(deltaTime);
        lastFrame = currentFrame;

        Scene::m_Camera->HandleInput(window);
        Scene::m_Camera->Update();

        scene->Update();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    Utils::WindowHeight = height;
    Utils::WindowWidth = width;
}
