#version 430 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 v_normal;

uniform mat4 u_VP;
uniform mat4 u_model;

out vec3 f_pos;
out vec3 f_normal;

void main()
{
	f_normal = vec3(u_model * vec4(v_normal, 1.0));
	f_pos = vec3(u_model * vec4(position, 1.0));
	gl_Position = u_VP * u_model * vec4(position, 1);
}