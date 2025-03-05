#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "../Shader/Shader.h"
#include "../Renderable/Renderable.h"
#include "../Components/Component.h"
#include "../Scene/Scene.h"


class Plane : Renderable{
public:
    Plane(const Shader& shader);
    ~Plane();

    void Draw() override;
    void Update() override;

    void Scale(glm::vec3 scale);
    void Rotate(float degrees, glm::vec3 scalingVector);

    void SetPosition(glm::vec3 pos);
    void SetShader(Shader& shader);

    const glm::vec3& GetPosition();

private:
    std::vector<Component*> m_Components;

    glm::mat4 m_Model;
    glm::vec3 m_Position;
    unsigned int m_VBO;
    unsigned int m_VAO;
    unsigned int m_EBO;
    Shader m_Shader;
    static bool m_Initialized;
};