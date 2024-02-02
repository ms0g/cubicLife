#version 410 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inTexCoord;
layout (location = 2) in float inTexType;
layout (location = 3) in mat4 instanceMatrix;

uniform mat4 view;
uniform mat4 projection;

out vec2 vTexCoord;
out float vTextType;

void main() {
    gl_Position = projection * view  * instanceMatrix * vec4(inPos, 1.0);

    vTexCoord = vec2(inTexCoord.x, inTexCoord.y);
    vTextType = inTexType;

}