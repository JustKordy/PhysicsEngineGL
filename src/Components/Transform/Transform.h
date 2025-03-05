#pragma once
#include "../Component.h"
#include <glm/glm.hpp>


class Transform: public Component {
public:
    Transform();
    Transform(glm::vec3 startPosition);
    ~Transform();


    void Update();
    void SetPosition(glm::vec3 position);

    const glm::vec3& GetPosition();
    
private:
    glm::vec3 m_Position;
};