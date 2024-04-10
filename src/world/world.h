#pragma once

#include <vector>
#include <unordered_map>
#include "glm/glm.hpp"

class Cell;
class CellMesh;
class Shader;
class World {
public:
    World();

    ~World();

    struct Info {
        uint64_t generationCount;
        uint32_t aliveCellCount;
    };

    [[nodiscard]] Info getInfo() const { return mInfo; }

    void update();

    void draw(glm::mat4 view, glm::mat4 projection);



private:
    void processNeighbors(Cell& cell);

    void checkNeighbor(Cell& currentAlive, glm::vec3 neighPos);

    Info mInfo{};
    uint64_t mGenerationCount{0};

    std::unordered_map<int, Cell> mAliveCells;
    std::vector<int> mCurrentDeadCellIndexes;
    std::vector<Cell> mNeighboringDeadCells;

    // For instancing
    std::unique_ptr<Shader> mShader;
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

    std::vector<glm::vec3> mCellPositions = {
            // Left Cube
            {0.0f,   0.0f,  0.0f},
            {1.0f,   0.0f,  0.0f},
            {0.0f,   0.0f,  1.0f},
            {1.0f,   0.0f,  1.0f},
            // First Spaceship
            {10.0f,  0.0f,  0.0f},
            {10.0f,  0.0f,  1.0f},
            {10.0f,  0.0f,  2.0f},
            {11.0f,  0.0f, -1.0f},
            {12.0f,  0.0f, -2.0f},
            {13.0f,  0.0f, -2.0f},
            {11.0f,  0.0f,  3.0f},
            {12.0f,  0.0f,  4.0f},
            {13.0f,  0.0f,  4.0f},
            {14.0f,  0.0f,  1.0f},
            {15.0f,  0.0f, -1.0f},
            {15.0f,  0.0f,  3.0f},
            {16.0f,  0.0f,  0.0f},
            {16.0f,  0.0f,  1.0f},
            {16.0f,  0.0f,  2.0f},
            {17.0f,  0.0f,  1.0f},
            // Second Spaceship
            {20.0f,  0.0f,  0.0f},
            {20.0f,  0.0f, -1.0f},
            {20.0f,  0.0f, -2.0f},
            {21.0f,  0.0f,  0.0f},
            {21.0f,  0.0f, -1.0f},
            {21.0f,  0.0f, -2.0f},
            {22.0f,  0.0f,  1.0f},
            {22.0f,  0.0f, -3.0f},
            {24.0f,  0.0f, -3.0f},
            {24.0f,  0.0f, -4.0f},
            {24.0f,  0.0f,  1.0f},
            {24.0f,  0.0f,  2.0f},
            // Right Cube
            {34.0f,  0.0f, -2.0f},
            {34.0f,  0.0f, -1.0f},
            {35.0f,  0.0f, -2.0f},
            {35.0f,  0.0f, -1.0f},
    };
};
