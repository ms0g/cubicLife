#version 410 core

in vec2 vTexCoord;

uniform sampler2D texture1;

out vec4 fragColor;


void main() {
    fragColor = texture(texture1, vTexCoord);
}