#version 330 core

in vec2 textureCoords;

uniform sampler2D u_texture;

out vec4 fragColor;

void main() {

	fragColor = texture(u_texture, textureCoords);

}