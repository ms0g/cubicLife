#version 410 core

in vec3 vNorm;
in vec2 vTexcoord;

uniform sampler2D texture1;

out vec4 fragColor;

void main() {
    fragColor = texture(texture1, vTexcoord);
}