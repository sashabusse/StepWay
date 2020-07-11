#version 430
layout(local_size_x = 1, local_size_y = 1) in;

layout(r32f) uniform image2D img_input;
layout(r32f) uniform image2D img_output;

uniform float intencity;

uniform float dt;
uniform float h;
uniform float a;

void main() {
	ivec2 pix_coords = ivec2(gl_GlobalInvocationID.xy);
	int i = pix_coords.x;
	int j = pix_coords.y;

	float Unm = imageLoad(img_input, ivec2(i, j)).r;

	int N = 512;
	if (i == 0)
	{
		imageStore(img_output, pix_coords, vec4(50.0, 0.0, 0.0, 1.0));
	}
	else if (i == N - 1)
	{
		imageStore(img_output, pix_coords, vec4(50.0, 0.0, 0.0, 1.0));
	}
	else
	{
		float Unm_p = imageLoad(img_input, ivec2(i + 1, j)).r;
		float Unm_m = imageLoad(img_input, ivec2(i - 1, j)).r;

		float pix_new = Unm + dt / (h * h) * a * a * (Unm_p + Unm_m - 2 * Unm);

		imageStore(img_output, pix_coords, vec4(pix_new, 0.0, 0.0, 0.0));
	}
}