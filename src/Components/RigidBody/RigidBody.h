#pragma once
#include <glm/glm.hpp>
#include "../Component.h"
#include "../../Logger/Logger.h"

class RigidBody : public Component {
public:
    RigidBody();
    ~RigidBody();

    void Update() override;
  
    void SetVelocity(glm::vec3 vel);
    void SetAcceleration(glm::vec3 acc);
    void SetMass(float mass);

    const glm::vec3& GetVelocity();
    const glm::vec3& GetAcceleration();
    const float& GetMass();

private:
    glm::vec3 m_Velocity;
    glm::vec3 m_Acceleration;
    float m_Mass;

};