#version 460 core

in vec3 ourColor;
in flat int isColorOut;
in vec2 TexCoord;

out vec4 finalColor;

uniform sampler2D ourTexture;

void main() {
	if (isColorOut == 1)
		finalColor = vec4(ourColor, 1.0);
	else
		finalColor = texture(ourTexture, TexCoord);	
}