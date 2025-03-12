#include "Cube.h"
#include <GL/glew.h>
#include "../../Logger/Logger.h"
#include "../../Scene/Scene.h"
#include "../../Components/Transform/Transform.h"
#include "../../Shader/Shader.h"

unsigned int Cube::m_VAO = 0;
unsigned int Cube::m_VBO = 0;
unsigned int Cube::m_EBO = 0;
bool Cube::m_Initialized = false;

Cube::Cube(const Shader& shader) : m_Shader(shader), m_Model(glm::mat4(1.f))
{
    if (!m_Initialized)
    {

        float vertices[] = {
            //zadni
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 

            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 
            -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 
            

            // predni
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 

            //leva
            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,  
            -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 

            //prava
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 

            //dolni
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 
            -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 

            //horni
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 
            0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        };
       

        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);

        // Generate and bind the VBO
        glGenBuffers(1, &m_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Set vertex attribute pointers
        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        // Texture coordinate attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        
    }  
    m_Scale = glm::vec3(1.f);
}

Cube::~Cube()
{
}

void Cube::Draw()
{
    m_Shader.use();
    m_Shader.setMat4("u_Projection", Scene::m_Camera->GetProjection());
    m_Shader.setMat4("u_View", Scene::m_Camera->GetView());
    m_Shader.setVec4("u_Color", m_Color);
    m_Shader.setMat4("u_Model", m_Model);

    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void Cube::Update()
{
    if(auto* trans = this->GetComponent<Transform>())
    {
        glm::mat4 tr = glm::mat4(1.f);
        tr = glm::translate(tr, trans->GetPosition());
        tr = glm::scale(tr, m_Scale);
        this->m_Model = tr;
    }
    else{
        Logger::Error("Couldnt get the transform component");
    }
}

void Cube::SetAcceleration(glm::vec3&& acc)
{
    this->m_Acceleration = acc;
}
void Cube::SetMass(float mass)
{
    this->m_Mass = mass;
}

void Cube::SetShader(const Shader& shader)
{
    this->m_Shader = shader;
}

void Cube::SetColor(glm::vec4 color)
{
   this->m_Color = color;
}

void Cube::Scale(glm::vec3 scale)
{
    this->m_Scale = scale;
}

void Cube::Rotate(float degrees, glm::vec3 rotationVector)
{
    this->m_Model = glm::rotate(m_Model, glm::radians(degrees), rotationVector);
}


const glm::vec3 &Cube::GetVelocity() const
{
    return this->m_Velocity;
}
const glm::vec3 &Cube::GetAcceleration() const
{
    return this->m_Acceleration;
}

const float &Cube::GetMass() const
{
    return this->m_Mass;
}
