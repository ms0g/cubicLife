#version 410 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inNorm;
layout (location = 2) in vec2 inTexCoord;
layout (location = 3) in float inTexType;
layout (location = 4) in mat4 instanceMatrix;

uniform mat4 view;
uniform mat4 projection;

out vec2 vTexCoord;
out vec3 vNormal;
out vec3 vFragPos;
out float vTextType;

void main() {
    vFragPos = vec3(instanceMatrix * vec4(inPos, 1.0));
    vNormal = mat3(transpose(inverse(instanceMatrix))) * inNorm;
    vTexCoord = inTexCoord;
    vTextType = inTexType;
    gl_Position = projection * view  * vec4(vFragPos, 1.0);
}