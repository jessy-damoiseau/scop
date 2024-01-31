#ifndef TEXTURE_HPP
#define TEXTURE_HPP


#include <header.hpp>


class Texture {
public:
    Texture(const char *);
    ~Texture();

    void bind() const;
    void unbind() const;

private:
    GLuint  _textureID;
    int     _width;
    int     _height;
    int     _nrChannels;
    unsigned char *data;
};

#endif