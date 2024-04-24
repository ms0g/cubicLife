#version 410 core

layout (location = 0) in vec3 pos;

uniform mat4 projection;
uniform mat4 view;

out vec3 vTexCoord;

void main() {
    vTexCoord = pos;
    vec4 pos = projection * view * vec4(pos, 1.0);
    gl_Position = pos.xyww;
}