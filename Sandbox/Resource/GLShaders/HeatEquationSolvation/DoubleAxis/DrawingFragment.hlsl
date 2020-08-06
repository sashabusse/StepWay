#version 430 core

layout(location = 0) out vec4 color;

in vec2 TexCoord;
uniform sampler2D ourTexture;

void main()
{
	float tex_r = texture(ourTexture, TexCoord + vec2(0.5, 0.5)).r / 100.0;
	color = vec4(tex_r, 0.1, 1.0 - tex_r, 1.0);
	//float r = texture(ourTexture, TexCoord + vec2(0.5, 0.5)).r / 100;
	//vec2 coord = TexCoord + vec2(0.5, 0.5);
	//float y = coord.y;
	//float brightness = 1.0 / (1 + 500 * (r - y) * (r - y));
	//color = vec4(brightness, brightness, brightness, 1.0);
};