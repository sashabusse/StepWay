#version 430 core

layout(location = 0) in vec4 position;

out vec2 TexCoord;

void main()
{
	TexCoord = position.xy;
	gl_Position = position;
}