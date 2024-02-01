#version 410 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inTexCoord;
layout (location = 2) in float inTexType;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 vTexCoord;
out float vTextType;

void main() {
    vTexCoord = vec2(inTexCoord.x, inTexCoord.y);
    vTextType = inTexType;
    gl_Position = projection * view  * model * vec4(inPos, 1.0);

}