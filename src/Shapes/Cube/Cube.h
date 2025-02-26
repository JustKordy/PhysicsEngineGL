#pragma once
#include "../Shape.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../../Shader/Shader.h"


class Cube : Shape
{
public:
    Cube(const glm::vec3 &pos, float mass);
    ~Cube();

    void Draw(Shader &shader, glm::vec3 position, glm::vec3 scale);



    void Update() const override;
    void SetPosition() const override;
    void SetAcceleration() const override;
    void SetMass() const override;
    
    glm::vec3& GetPosition() const override;
    glm::vec3& GetVelocity() const override;
    glm::vec3& GetAcceleration() const override;

    float& GetMass() const override;


    static bool m_Initialized;
    static unsigned int m_VBO, m_VAO, m_EBO;

private:
    glm::vec3 m_Positon;
    glm::vec3 m_Velocity;
    glm::vec3 m_Acceleration;
    float m_Mass;

};