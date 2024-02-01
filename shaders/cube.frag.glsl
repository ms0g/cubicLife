#version 410 core

in vec2 vTexCoord;
in float vTextType;

uniform sampler2D texture1;
uniform sampler2D texture2;

out vec4 fragColor;

void main() {
    if (vTextType == 0.0) {
        fragColor = texture(texture1, vTexCoord);
    } else {
        fragColor = texture(texture2, vTexCoord);
    }
}