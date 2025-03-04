#pragma once
#include <glm/glm.hpp>
#include "../Renderable/Renderable.h"


class Shape : Renderable{
public:
    
    virtual void Update() = 0;
    virtual void SetPosition(glm::vec3 && pos) = 0;
    virtual void SetAcceleration(glm::vec3&& acc) = 0;
    virtual void SetMass(float mass) = 0;
    
    
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