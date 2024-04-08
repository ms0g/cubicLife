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

    void checkNeighbor(Cell& currentAlive, Cell& neigh);

    std::unordered_map<int, Cell> mAliveCells;
    std::vector<Cell> mNeighboringDeadCells;
    std::unordered_set<int> mCurrentDeadCellIndexes;
    std::unique_ptr<Shader> mShader;

    std::vector<glm::vec3> cellPositions = {
            {0.0f,  0.0f,  0.0f},
            {1.0f,  0.0f,  0.0f},
            {2.0f,  0.0f,  0.0f},
            {3.0f,  0.0f,  0.0f},
            {2.0f,  0.0f,  -1.0f},
            {3.0f,  0.0f,  -1.0f},
            {4.0f,  0.0f,  -1.0f},
            {5.0f,  0.0f,  -1.0f},
            {6.0f,  0.0f,  -1.0f},
            {7.0f,  0.0f,  -1.0f},
            {6.0f,  0.0f,  -2.0f},
            {7.0f,  0.0f,  -2.0f},
            {7.0f,  0.0f,  -3.0f},
            {8.0f,  0.0f,  -2.0f},
            {8.0f,  0.0f,  -3.0f}
    };
};
