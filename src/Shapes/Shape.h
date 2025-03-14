#pragma once
#include <glm/glm.hpp>
#include "../Renderable/Renderable.h"


class Shape : public Renderable{
public:
    
    virtual void Update() = 0;
    
    virtual void Scale(glm::vec3 scale) = 0;
    virtual void Rotate(float degrees, glm::vec3 rotationVector) = 0;

};