#pragma once
#include "../Component.h"
#include "../../Logger/Logger.h"

class RigidBody : public Component {
public:
    RigidBody(){

    }
    ~RigidBody(){

    }

    void Update() override {
        
    }
    void Hello(){
        Logger::Log("HELLO FROM RG");
    }

};