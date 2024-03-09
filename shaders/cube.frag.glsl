#version 410 core

in vec2 vTexCoord;
in float vTextType;

struct Texture {
    sampler2D texture1;
    sampler2D texture2;
};

uniform Texture tex;

out vec4 fragColor;

void main() {
    if (vTextType == 0.0) {
        fragColor = texture(tex.texture1, vTexCoord);
    } else {
        fragColor = texture(tex.texture2, vTexCoord);
    }
}