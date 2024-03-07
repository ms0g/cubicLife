#version 410 core

in vec2 vTexCoord;
in float vTextType;
in vec3 vNormal;
in vec3 vFragPos;

struct Light {
    //vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Texture {
    sampler2D texture1;
    sampler2D texture2;
};

uniform Light light;
uniform Texture _texture;
uniform vec3 viewPos;

out vec4 fragColor;

void main() {
    vec3 textureColor;
    if (vTextType == 0.0) {
        textureColor = texture(_texture.texture1, vTexCoord).rgb;
    } else {
        textureColor = texture(_texture.texture2, vTexCoord).rgb;
    }
    // ambient
    vec3 ambient = light.ambient * textureColor;

    // diffuse
    vec3 norm = normalize(vNormal);
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * textureColor;

    // specular
    vec3 viewDir = normalize(viewPos - vFragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = light.specular * spec * textureColor;

    vec3 result = ambient + diffuse + specular;

    fragColor = vec4(result, 1.0);
}