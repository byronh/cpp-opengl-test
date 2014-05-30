#version 330 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_textureCoords;
layout (location = 2) in vec3 a_normal;
layout (location = 3) in mat4 a_modelViewProjection;
layout (location = 7) in mat4 a_world;

out vec2 v_textureCoords;
out vec3 v_normal;
out vec3 v_world;

void main() {

	v_textureCoords = a_textureCoords;
	v_normal = (a_world * vec4(a_normal, 0.0)).xyz;
	v_world = (a_world * vec4(a_position, 0.0)).xyz;
	
	gl_Position = a_modelViewProjection * vec4(a_position, 1.0);
}

