#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_textureCoords;

uniform mat4 u_modelViewProjection;

out vec2 textureCoords;

void main() {

	textureCoords = a_textureCoords;
	gl_Position = u_modelViewProjection * vec4(a_position, 1.0);
	
}

