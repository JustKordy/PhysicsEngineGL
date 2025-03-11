#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "../Shader/Shader.h"
#include "../Renderable/Renderable.h"
#include "../Components/Component.h"



class Plane : public Renderable{
public:
    Plane(const Shader& shader);
    ~Plane();

    void Draw() override;
    void Update() override;

    void SetTexture(const char* path);

    void Scale(glm::vec3 scale);
    void Rotate(float degrees, glm::vec3 scalingVector);

    void SetShader(Shader& shader);

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
    T* AddComponent(Targs&&... args){
        T* comp = new T(std::forward<Targs>(args)...);
        m_Components.push_back(comp);
        return comp;
     
    }
    

private:
    std::vector<Component*> m_Components;

    glm::mat4 m_Model;
    unsigned int m_VBO;
    unsigned int m_VAO;
    unsigned int m_EBO;
    Shader m_Shader;
    static bool m_Initialized;
    unsigned int m_Texture;
};