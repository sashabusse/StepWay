#version 430 core
layout (location = 0) out vec4 color;

uniform vec4 u_color;

in vec3 f_pos;
in vec3 f_normal;


void main()
{
	vec3 light_color = vec3(1.0, 1.0, 1.0);

	float ambient_strength = 0.1;
	vec3 ambient = ambient_strength * light_color;

	vec3 light_pos = vec3(0.0, 1.5, -1.0);

	vec3 norm = normalize(f_normal);
	vec3 light_dir = normalize(light_pos - f_pos);

	float diff = max(dot(norm, light_dir), 0.0);
	vec3 diffuse = diff * light_color;

	vec3 result = (ambient + diffuse) * u_color.xyz;
	color = vec4(result, 1.0);//vec4(abs(norm), 1.0);
};