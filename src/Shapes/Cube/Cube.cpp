#include "Cube.h"
#include <GL/glew.h>

unsigned int Cube::m_VAO = 0;
unsigned int Cube::m_VBO = 0;
unsigned int Cube::m_EBO = 0;
bool Cube::m_Initialized = false;

Cube::Cube(const Shader& shader) : m_Shader(shader)
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
}

Cube::~Cube()
{
}

void Cube::Draw()
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, this->m_Positon);
    model = glm::scale(model, glm::vec3(1.f));

    this->m_Shader.setMat4("u_Model", model);

    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void Cube::Update()
{
}
void Cube::SetPosition(glm::vec3&& pos)
{
    this->m_Positon = pos;
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

const glm::vec3 &Cube::GetPosition() const
{
    return this->m_Positon;
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
