#version 430
layout(local_size_x = 1, local_size_y = 1) in;
layout(rgba32f, binding = 0) uniform image2D img_output;

uniform float multiplier;

void main() {
	vec4 pixel = vec4(0.0, 1.0, 1.0, 1.0);
	ivec2 pixel_coords = ivec2(gl_GlobalInvocationID.xy);
	pixel.r = multiplier*pixel_coords.x * 1.0 / 512.0;
	imageStore(img_output, pixel_coords, pixel);
}