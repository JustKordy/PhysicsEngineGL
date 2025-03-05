#include "Plane.h"
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include "../Utils/Utils.h"
#include "../Logger/Logger.h"
#include "../Components/Transform/Transform.h"

bool Plane::m_Initialized = false;

Plane::Plane(const Shader& shader) : m_Shader(shader), m_Model(glm::mat4(1.f))
{
    if(!m_Initialized)
    {
        float planeVertices[] = {
            // Positions        // Normals         // Tex Coords
            -5.0f, 0.0f, -5.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, // Bottom-left
             5.0f, 0.0f, -5.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // Bottom-right
            -5.0f, 0.0f,  5.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f, // Top-left
             5.0f, 0.0f,  5.0f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f  // Top-right
        };
        
        unsigned int indices[] = {0, 1, 2, 1, 3, 2};
    
        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);

        glGenBuffers(1, &m_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);

        glGenBuffers(1, &m_EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);

        m_Initialized = true;
    
    }
}

Plane::~Plane()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
}

void Plane::Update() {
    for(int i = 0; i < m_Components.size(); i++)
    {
        m_Components[i]->Update();
    }

    if(auto* comp = this->GetComponent<Transform>())
    {
        glm::mat4 tr = glm::mat4(1.f);
        tr = glm::translate(tr, comp->GetPosition());
        this->m_Model = tr;
    }
    else{
        Logger::Error("Couldnt find the transform component");
    }
}

void Plane::SetTexture(const char *path)
{
    unsigned int text = Utils::LoadTexture(Utils::GetResourcePath(path).c_str());
    if(text)
    {
        this->m_Texture = text;
    }
    else{
        Logger::Log("Failed to load texture with path:", path);
    }
}

void Plane::Scale(glm::vec3 scale)
{
    this->m_Model = glm::scale(m_Model, scale);
}

void Plane::Rotate(float degrees, glm::vec3 scalingVector)
{
    this->m_Model = glm::rotate(m_Model, glm::radians(degrees), scalingVector);
}

void Plane::Draw()
{   
    this->m_Shader.use();
    this->m_Shader.setMat4("u_Projection", Scene::m_Camera->GetProjection());
    this->m_Shader.setMat4("u_View", Scene::m_Camera->GetView());
    this->m_Shader.setMat4("u_Model", m_Model);
     
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_Texture);
    this->m_Shader.setInt("tex", 0);
 
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Plane::SetShader(Shader& shader)
{
    this->m_Shader = shader;
}
