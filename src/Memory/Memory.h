#pragma once
#include "../Shapes/Cube/Cube.h"

class Memory{
public:

    template<typename T>
    static void Clean(T* obj)
    {
        if(auto* cube = dynamic_cast<Cube*>(obj))
        {
            delete cube;
        }
    }
};