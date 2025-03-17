#ifndef CAE_RENDERER_H
#define CAE_RENDERER_H

#include "shader.h"
#include "skybox.h"
#include "mesh/cellMesh.h"


class Cell;
class Renderer {
public:
    Renderer();

    void render(const glm::mat4& view, const glm::mat4& projection,
        const std::unordered_map<std::string, Cell>& aliveCells) const;

    void clear(float r, float g, float b, float a);

private:
    std::unique_ptr<Shader> cellShader;
    std::unique_ptr<CellMesh> cellMesh;
    std::unique_ptr<Skybox> skybox;

    std::vector<float> cellVertices = {
            // Back face
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f, // Bottom-left
            0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  1.0f, 1.0f, // top-right
            0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  1.0f, 0.0f, // bottom-right
            0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  1.0f, 1.0f, // top-right
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f, // bottom-left
            -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  0.0f, 1.0f, // top-left
            // Front face
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f,  0.0f, 0.0f, // bottom-left
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f,  1.0f, 0.0f, // bottom-right
            0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  1.0f,  1.0f, 1.0f, // top-right
            0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  1.0f,  1.0f, 1.0f, // top-right
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  1.0f,  0.0f, 1.0f, // top-left
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f,  0.0f, 0.0f, // bottom-left
            // Left face
            -0.5f,  0.5f,  0.5f, -1.0f, 0.0f,  0.0f,  1.0f, 1.0f, // top-right
            -0.5f,  0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  0.0f, 1.0f, // top-left
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  0.0f, 0.0f, // bottom-left
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  0.0f, 0.0f, // bottom-left
            -0.5f, -0.5f,  0.5f, -1.0f, 0.0f,  0.0f,  1.0f, 0.0f, // bottom-right
            -0.5f,  0.5f,  0.5f, -1.0f, 0.0f,  0.0f,  1.0f, 1.0f, // top-right
            // Right face
            0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f,  1.0f, 1.0f, // top-left
            0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.0f, 0.0f, // bottom-right
            0.5f,  0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.0f, 1.0f, // top-right
            0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.0f, 0.0f, // bottom-right
            0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f,  1.0f, 1.0f, // top-left
            0.5f, -0.5f,  0.5f, 1.0f,  0.0f,  0.0f,  1.0f, 0.0f, // bottom-left
            // Bottom face
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f,  0.0f, 1.0f, // top-right
            0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f,  1.0f, 1.0f, // top-left
            0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f,  1.0f, 0.0f, // bottom-left
            0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f,  1.0f, 0.0f, // bottom-left
            -0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f,  0.0f, 0.0f, // bottom-right
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f,  0.0f, 1.0f, // top-right
            // Top face
            -0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f, // top-left
            0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f,  1.0f, 0.0f, // bottom-right
            0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f,  1.0f, 1.0f, // top-right
            0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f,  1.0f, 0.0f, // bottom-right
            -0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f, // top-left
            -0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f,  0.0f, 0.0f, // bottom-left
    };
};

#endif //CAE_RENDERER_H
