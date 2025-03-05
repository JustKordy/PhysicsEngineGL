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
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "Components/RigidBody/RigidBody.h"
#include "Shapes/Cube/Cube.h"
#include "Renderer/Renderer.h"
#include "Plane/Plane.h"
#include "Scene/Scene.h"

void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

float deltaTime = 0.0f;
float lastFrame = 0.0f;


Camera* Scene::m_Camera = new Camera();
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

    GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    glewExperimental = GL_FALSE;
    glewInit();

    int viewportWidth, viewportHeight;
    glfwGetFramebufferSize(window, &viewportWidth, &viewportHeight);
    glViewport(0, 0, viewportWidth, viewportHeight);

    glEnable(GL_DEPTH_TEST);

    Shader cubeShader(Utils::GetResourcePath("/shaders/cube.vert").c_str(), Utils::GetResourcePath("/shaders/cube.frag").c_str());
    Shader planeShader(Utils::GetResourcePath("/shaders/plane.vert").c_str(), Utils::GetResourcePath("/shaders/plane.frag").c_str());

    
    Scene* scene = new Scene();
    Cube* cube = new Cube(cubeShader);
    Plane* plane = new Plane(planeShader);

    

    cube->SetPosition(glm::vec3(0.f, 1.f, -8.f));
    cube->Scale(glm::vec3(.3f));
    plane->SetPosition(glm::vec3(0.f, -2.f, -8.f));


    unsigned int transparentTexture = Utils::LoadTexture(Utils::GetResourcePath("transBack.png").c_str());
    

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");



    while (!glfwWindowShouldClose(window))
    {

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        Utils::SetDeltaTime(deltaTime);
        lastFrame = currentFrame;

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Scene::m_Camera->HandleInput(window);
        Scene::m_Camera->Update();

       
        
        Renderer::Render(cube); 
        
      
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, transparentTexture);
        planeShader.setInt("tex", 0);
        Renderer::Render(plane);
        

        ImGui::Begin("Template");
        ImGui::Text("Some text");
        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    Utils::WindowHeight = height;
    Utils::WindowWidth = width;
}

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
{
    Scene::m_Camera->HandleLook(xposIn, yposIn, Utils::isMouseClicked());
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        Utils::SetMouseClicked(true);
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
        Utils::SetMouseClicked(false);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    Scene::m_Camera->HandleZoom(yoffset);
}