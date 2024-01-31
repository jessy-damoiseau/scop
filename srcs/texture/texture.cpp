#include <texture/texture.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

Texture::Texture(const char *path)
{
    glGenTextures(1, &this->_textureID);
    glBindTexture(GL_TEXTURE_2D, this->_textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_set_flip_vertically_on_load(true);
    
    this->data = stbi_load(path, &this->_width, &this->_height, &this->_nrChannels, 0);
    if (!this->data) {
        std::cout << "Failed to load texture: " << path << std::endl;
    }
    else {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(this->data);
    }
}

Texture::~Texture()
{
    glDeleteTextures(1, &this->_textureID);
}

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, this->_textureID);
}

void Texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
