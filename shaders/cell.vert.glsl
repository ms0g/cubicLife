#version 410 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 norm;
layout (location = 2) in vec2 texcoord;
layout (location = 3) in mat4 instanceMatrix;

uniform mat4 view;
uniform mat4 projection;

out vec3 vNorm;
out vec2 vTexcoord;

void main() {
    vNorm = norm;
    vTexcoord = texcoord;
    gl_Position = projection * view  * instanceMatrix * vec4(pos, 1.0);
}