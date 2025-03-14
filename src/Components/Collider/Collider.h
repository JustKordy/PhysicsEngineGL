#pragma once
#include "../Component.h"

class Collider : public Component{
public:
    Collider();
    ~Collider();

    void Update() override;

private:
    bool m_Active;

};