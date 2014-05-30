#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_textureCoords;

uniform mat4 MVP;

out vec2 textureCoords;

void main() {

	textureCoords = a_textureCoords;
	gl_Position = MVP * vec4(a_position, 1.0);
	
}

