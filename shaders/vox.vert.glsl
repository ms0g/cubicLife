#version 410 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 vTexCoord;

void main() {
    vTexCoord = vec2(inTexCoord.x, inTexCoord.y);
    gl_Position = projection * view  * model * vec4(inPos, 1.0);

}