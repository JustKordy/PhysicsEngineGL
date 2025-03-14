#pragma once
#include "../Shape.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../../Shader/Shader.h"
#include "../../Components/Component.h"
#include <vector>


class Cube : public Shape
{
public:
    Cube(const Shader& shader);
    ~Cube();

    void Draw() override;
    void Update() override;
    void SetShader(const Shader& shader);
    void SetColor(glm::vec4 color);

    void Scale(glm::vec3 scale) override;
    void Rotate(float degrees, glm::vec3 rotationVector) override;

    template<typename T>
    T* GetComponent() 
    {
        for(Component* comp : m_Components)
        {
            if(T* component = dynamic_cast<T*>(comp)){
                return component;
            }   
        }
        return nullptr;
    }

    template<typename T, typename... Targs>
    T* AddComponent(Targs&&... args) 
    {
        T* comp = new T(std::forward<Targs>(args)...);
        m_Components.push_back(comp);
        return comp;
     
    }

    static bool m_Initialized;
    static unsigned int m_VBO, m_VAO, m_EBO;

private: 
    glm::mat4 m_Model;
    glm::vec4 m_Color;
    glm::vec3 m_Scale;
    Shader m_Shader;
    std::vector<Component*> m_Components;
};