#include "Utils.h"
#include <GL/glew.h>
#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image/stb_image.h"
#include "../Logger/Logger.h"


float Utils::m_DeltaTime = 0.0f;
bool Utils::MouseClicked = false;
int Utils::WindowHeight = 900;
int Utils::WindowWidth = 1280;

unsigned int Utils::LoadTexture(const char* path) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    stbi_set_flip_vertically_on_load(true); 
    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3 || nrComponents == 1)
            format = GL_RGB;
        else if (nrComponents == 4 || nrComponents == 1)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        stbi_image_free(data);
        Logger::Log("Successfully loaded texture", path , "with", nrComponents, "channels");
    }
    else
    {
        Logger::Log("Texture failed to load at path", path);
        stbi_image_free(data);
    }

    return textureID;
}

std::string Utils::GetResourcePath(const std::string &file)
{
    return std::string(PROJECT_ROOT_DIR) + "/resources/" + file;
    Logger::Log(PROJECT_ROOT_DIR);
}
