#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Shader;
struct Vertex {
#define MAX_BONE_INFLUENCE 4
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
    //bone indexes which will influence this vertex
    int m_BoneIDs[MAX_BONE_INFLUENCE];
    //weights from each bone
    float m_Weights[MAX_BONE_INFLUENCE];
};

struct Texture {
    unsigned int id;
    std::string name;
    std::string path;
};

class Mesh {
public:
    Mesh(std::vector<float>& vertices, std::vector<Texture>& textures);

    // render the mesh
    void render();

private:
    // initializes all the buffer objects/arrays
    void setup();
    // mesh Data
    std::vector<float> m_vertices;
    std::vector<Texture> m_textures;
    unsigned int m_VAO{};
    unsigned int m_VBO{};


};