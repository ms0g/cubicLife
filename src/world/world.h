#pragma once

#include <vector>
#include <unordered_map>
#include "glm/glm.hpp"
#include "mesh/texture.h"
#include "filesystem/filesystem.h"
#include "../configs/configs.hpp"

class Cell;
class CellMesh;
class Shader;
class World {
public:
    World(const std::vector<glm::vec3>& initialState);

    ~World();

    struct State {
        uint64_t generationCount;
        uint32_t aliveCellCount;
    };

    [[nodiscard]] State state() const { return mState; }

    void update();

    void draw(glm::mat4 view, glm::mat4 projection);

private:
    void processNeighbors(Cell& cell, float y);

    void checkNeighbor(Cell& currentAlive, glm::vec3 neighPos);

    State mState{};
    uint64_t mGenerationCount{0};

    std::unordered_map<uint64_t, Cell> mAliveCells;
    std::vector<uint64_t> mCurrentDeadCellIndexes;
    std::vector<Cell> mNeighboringDeadCells;

    // For instancing
    std::unique_ptr<Shader> mShader;
    std::unique_ptr<CellMesh> mMesh;

    std::vector<float> mVertices = {
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

    std::vector<Texture> mTextures = {
            {texture::load(fs::path(ASSET_DIR + "glowing-rocks.jpg").c_str()),
                    "texture1",
                    "glowing-rocks.jpg"}
    };
};
