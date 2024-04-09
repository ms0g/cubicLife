#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "glm/glm.hpp"

class Cell;
class Shader;
class World {
public:
    World();

    ~World();

    void update();

    void draw(glm::mat4 view, glm::mat4 projection);

private:
    void processNeighbors(Cell& cell);

    void checkNeighbor(Cell& currentAlive, glm::vec3 neighPos);

    std::unordered_map<int, Cell> mAliveCells;
    std::unordered_set<int> mCurrentDeadCellIndexes;
    std::vector<Cell> mNeighboringDeadCells;
    std::unique_ptr<Shader> mShader;

    std::vector<glm::vec3> cellPositions = {
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
