#pragma once
#include <glm/glm.hpp>


class Shape{
public:
    
    virtual void Update() const = 0;
    virtual void SetPosition() const = 0;
    virtual void SetAcceleration() const = 0;
    virtual void SetMass() const = 0;
    
    const virtual glm::vec3& GetPosition() const = 0;
    const virtual glm::vec3& GetVelocity() const = 0;
    const virtual glm::vec3& GetAcceleration() const = 0;

    const virtual float& GetMass() const = 0;


private: 
    glm::vec3 m_Positon;
    glm::vec3 m_Velocity;
    glm::vec3 m_Acceleration;
    float m_Mass;
};