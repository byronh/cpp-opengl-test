#version 330 core

in vec2 v_textureCoords;
in vec3 v_normal;
in vec3 v_world;
flat in int instanceID;

uniform sampler2D u_texture;

out vec4 fragColor;

void main() {

	fragColor = texture(u_texture, v_textureCoords);

}