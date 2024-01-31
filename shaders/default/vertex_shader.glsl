#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;
out flat int isColorOut;

uniform mat4 model;
uniform bool iscolor;


void main() {
    if (iscolor) {
        isColorOut = 1;
    } else {
        isColorOut = 0;
    }
    gl_Position = model * vec4(aPos, 1.0);
    ourColor = aColor;
    TexCoord = aTexCoord;
}