#pragma once
#include <glm/glm.hpp>
#include "../Shader/Shader.h"
#include "../Renderable/Renderable.h"

class Plane : Renderable{
public:
    Plane(const Shader& shader);
    ~Plane();

    void Draw();

    void SetPosition(glm::vec3& pos);
    void SetShader(Shader& shader);

    const glm::vec3& GetPosition();

private:
    glm::vec3 m_Position;
    unsigned int m_VBO;
    unsigned int m_VAO;
    unsigned int m_EBO;
    Shader m_Shader;
    static bool m_Initialized;
};