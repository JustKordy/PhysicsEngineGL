#pragma once
#include <glm/glm.hpp>
#include "../Renderable/Renderable.h"


class Shape : public Renderable{
public:
    
    virtual void Update() = 0;
    virtual void SetAcceleration(glm::vec3&& acc) = 0;
    virtual void SetMass(float mass) = 0;
    

    virtual void Scale(glm::vec3 scale) = 0;
    virtual void Rotate(float degrees, glm::vec3 rotationVector) = 0;
    
    const virtual glm::vec3& GetVelocity() const = 0;
    const virtual glm::vec3& GetAcceleration() const = 0;

    const virtual float& GetMass() const = 0;

};