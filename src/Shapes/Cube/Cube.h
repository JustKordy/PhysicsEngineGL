#pragma once
#include "../Shape.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../../Shader/Shader.h"


class Cube : Shape
{
public:
    Cube(const Shader& shader);
    ~Cube();

    void Draw();



    void Update() override;
    void SetPosition(glm::vec3&& position) override;
    void SetAcceleration(glm::vec3&& acc) override;
    void SetMass(float mass) override;
    void SetShader(const Shader& shader);
    
    const glm::vec3& GetPosition() const override;
    const glm::vec3& GetVelocity() const override;
    const glm::vec3& GetAcceleration() const override;

    const float& GetMass() const override;


    static bool m_Initialized;
    static unsigned int m_VBO, m_VAO, m_EBO;

private:
    glm::vec3 m_Positon;
    glm::vec3 m_Velocity;
    glm::vec3 m_Acceleration;
    float m_Mass;
    Shader m_Shader;

};