#version 430
layout(local_size_x = 1, local_size_y = 1) in;

layout(r32f) uniform image2D img_input;
layout(r32f) uniform image2D img_output;

uniform float intencity;

uniform float dt;
uniform float h;
uniform float a;
uniform float b_temp;

int N = 200;

void main() {
	ivec2 pix_coords = ivec2(gl_GlobalInvocationID.xy);
	int i = pix_coords.x;
	int j = pix_coords.y;

	float U = imageLoad(img_input, ivec2(i, j)).r;

	if (i == 0)
	{
		imageStore(img_output, pix_coords, vec4(b_temp, 0.0, 0.0, 1.0));
	}
	else if (i == N - 1)
	{
		imageStore(img_output, pix_coords, vec4(b_temp, 0.0, 0.0, 1.0));
	}
	else if (j == 0)
	{
		imageStore(img_output, pix_coords, vec4(b_temp, 0.0, 0.0, 1.0));
	}
	else if (j == N - 1)
	{
		imageStore(img_output, pix_coords, vec4(b_temp, 0.0, 0.0, 1.0));
	}
	else
	{
		float Ur = imageLoad(img_input, ivec2(i + 1, j)).r;
		float Ul = imageLoad(img_input, ivec2(i - 1, j)).r;
		float Uu = imageLoad(img_input, ivec2(i, j + 1)).r;
		float Ud = imageLoad(img_input, ivec2(i, j - 1)).r;

		float pix_new = U + dt / (h * h) * a * a * (Ur + Ul + Uu + Ud - 4 * U);

		imageStore(img_output, pix_coords, vec4(pix_new, 0.0, 0.0, 0.0));
	}
}