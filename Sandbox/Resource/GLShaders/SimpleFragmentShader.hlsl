#version 430 core
layout (location = 0) out vec4 color;
//layout(rgba32f, binding = 0) uniform image2D img_input;

in vec2 TexCoord;
uniform sampler2D ourTexture;
uniform vec4 u_color;

void main()
{
	//color = imageLoad(img_input, ivec2(int((TexCoord.x+0.5)*512),0));
	color = texture(ourTexture, TexCoord + vec2(0.5, 0));
};