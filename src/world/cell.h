#pragma once

#include <vector>
#include <memory>
#include "glm/glm.hpp"

class Shader;
class CellMesh;
class Cell {
public:
    explicit Cell(glm::vec3 pos);

    ~Cell();

    Cell(Cell&& other) noexcept;

    Cell& operator=(Cell&& other) noexcept;

    [[nodiscard]] int aliveNeighborsCount() const { return mAliveNeighbors; }

    void resetAliveNeighbors() { mAliveNeighbors = 0;}

    void incAliveNeighbors() { mAliveNeighbors++; }

    void update(glm::mat4 view, glm::mat4 projection, Shader& shader);

    void draw();

    bool operator==(const Cell &other) const {
        return (mPos.x == other.mPos.x && mPos.y == other.mPos.y && mPos.z == other.mPos.z) ;
    }

    glm::vec3 mPos{};

private:
    int mAliveNeighbors{0};
    glm::mat4 mModelMat{1.0f};
    std::unique_ptr<CellMesh> mMesh;

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
