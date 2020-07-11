#version 430 core

layout (location = 0) out vec4 color;

in vec2 TexCoord;
uniform sampler2D ourTexture;

void main()
{
	color = texture(ourTexture, TexCoord + vec2(0.5, 0));
};