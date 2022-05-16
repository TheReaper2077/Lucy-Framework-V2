#version 450 core

in vec3 normal;
in vec4 color;
in vec2 uv0;
in vec2 uv1;
in vec2 uv2;
in vec2 uv3;
in vec2 uv4;
in vec2 uv5;
in vec2 uv6;
in vec2 uv7;

in vec3 frag_pos;
in vec3 view_pos;

void main() {
	gl_FragColor = color;
}
