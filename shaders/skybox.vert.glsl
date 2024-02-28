#version 410 core

layout (location = 0) in vec3 inPos;

uniform mat4 projection;
uniform mat4 view;

out vec3 vTexCoord;

void main() {
    vTexCoord = inPos;
    vec4 pos = projection * view * vec4(inPos, 1.0);
    gl_Position = pos.xyww;
}