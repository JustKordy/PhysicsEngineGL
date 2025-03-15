#pragma once
#include "../Component.h"
#include "../../Shapes/Shape.h"

class Collider : public Component{
public:
    Collider(bool active = true);
    ~Collider();

    void Update() override;

private:
    bool m_IsActive{ true };
    bool m_IsTriggered{};


protected:
    Shape* m_Owner { nullptr };


};