#include "RigidBody.h"
#include "../../Utils/Utils.h"

RigidBody::RigidBody()
{
}

RigidBody::~RigidBody()
{
}

void RigidBody::Update()
{
    this->m_Velocity += this->m_Acceleration * Utils::GetDeltaTime();
}

void RigidBody::SetVelocity(glm::vec3 vel)
{
    this->m_Velocity = vel;
}

void RigidBody::SetAcceleration(glm::vec3 acc)
{
    this->m_Acceleration = acc;
}

void RigidBody::SetMass(float mass)
{
    this->m_Mass = mass;
}

const glm::vec3& RigidBody::GetVelocity()
{
    return this->m_Velocity;
}

const glm::vec3& RigidBody::GetAcceleration()
{
    return this->m_Acceleration;
}

const float &RigidBody::GetMass()
{
    return this->m_Mass;
}
