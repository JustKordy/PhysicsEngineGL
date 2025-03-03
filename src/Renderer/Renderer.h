#pragma once
#include "../Logger/Logger.h"
#include "../Shapes/Shape.h"
#include <GL/glew.h>


class Renderer{
public: 
    template<typename T>
    static void Render(T object){
        if(std::is_base_of_v<Shape, T>)
        {
            object.Draw();
        }
        else
        {
            Logger::Log("Object has to be derived from Shape class");
        }
    }
private: 

};