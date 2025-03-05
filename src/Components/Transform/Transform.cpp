#include "Transform.h"

Transform::Transform() : m_Position(glm::vec3(1.f))
{
}

Transform::Transform(glm::vec3 startPosition) : m_Position(startPosition)
{
}

Transform::~Transform()
{
}

void Transform::Update()
{

}

void Transform::SetPosition(glm::vec3 position)
{
    this->m_Position = position;
}

const glm::vec3 &Transform::GetPosition()
{
    return this->m_Position;   
}