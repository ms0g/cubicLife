#pragma once

#include <vector>
#include <memory>
#include "glm/glm.hpp"

class Shader;
class CubeMesh;
class Cube {
public:
    Cube();

    ~Cube();

    void update(glm::mat4 view, glm::mat4 modelMat, glm::mat4 projection);

    void draw();

private:
    std::unique_ptr<CubeMesh> mMesh;
    std::unique_ptr<Shader> mShader;

    std::vector<float> mVertices = {
            // Back face
            -0.5f, -0.5f, -0.5f, // Bottom-left
             0.5f,  0.5f, -0.5f, // top-right
             0.5f, -0.5f, -0.5f, // bottom-right
             0.5f,  0.5f, -0.5f, // top-right
            -0.5f, -0.5f, -0.5f, // bottom-left
            -0.5f,  0.5f, -0.5f, // top-left
            // Front face
            -0.5f, -0.5f,  0.5f, // bottom-left
             0.5f, -0.5f,  0.5f, // bottom-right
             0.5f,  0.5f,  0.5f, // top-right
             0.5f,  0.5f,  0.5f, // top-right
            -0.5f,  0.5f,  0.5f, // top-left
            -0.5f, -0.5f,  0.5f, // bottom-left
            // Left face
            -0.5f,  0.5f,  0.5f, // top-right
            -0.5f,  0.5f, -0.5f, // top-left
            -0.5f, -0.5f, -0.5f, // bottom-left
            -0.5f, -0.5f, -0.5f, // bottom-left
            -0.5f, -0.5f,  0.5f, // bottom-right
            -0.5f,  0.5f,  0.5f, // top-right
            // Right face
             0.5f,  0.5f,  0.5f, // top-left
             0.5f, -0.5f, -0.5f, // bottom-right
             0.5f,  0.5f, -0.5f, // top-right
             0.5f, -0.5f, -0.5f, // bottom-right
             0.5f,  0.5f,  0.5f, // top-left
             0.5f, -0.5f,  0.5f, // bottom-left
            // Bottom face
            -0.5f, -0.5f, -0.5f, // top-right
             0.5f, -0.5f, -0.5f, // top-left
             0.5f, -0.5f,  0.5f, // bottom-left
             0.5f, -0.5f,  0.5f, // bottom-left
            -0.5f, -0.5f,  0.5f, // bottom-right
            -0.5f, -0.5f, -0.5f, // top-right
            // Top face
            -0.5f,  0.5f, -0.5f, // top-left
             0.5f,  0.5f,  0.5f, // bottom-right
             0.5f,  0.5f, -0.5f, // top-right
             0.5f,  0.5f,  0.5f, // bottom-right
            -0.5f,  0.5f, -0.5f, // top-left
            -0.5f,  0.5f,  0.5f, // bottom-left
    };
};
