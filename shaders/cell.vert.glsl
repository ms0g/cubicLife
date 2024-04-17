#version 410 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inNorm;
layout (location = 2) in vec3 inTexcoord;
layout (location = 3) in mat4 instanceMatrix;

uniform mat4 view;
uniform mat4 projection;

out vec3 vNorm;
out vec2 vTexcoord;

void main() {
    vNorm = inNorm;
    vTexcoord = inTexcoord.xy;
    gl_Position = projection * view  * instanceMatrix * vec4(inPos, 1.0);
}