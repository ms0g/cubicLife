#version 410 core

in vec3 vTexCoord;

uniform samplerCube skybox;

out vec4 fragColor;

void main() {
    fragColor = texture(skybox, vTexCoord);
}