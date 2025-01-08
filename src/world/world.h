#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include "glm/glm.hpp"
#include "../core/io.hpp"
#include "../config/config.hpp"

class Cell;
class CellMesh;
class Shader;
class World {
public:
    World();

    ~World();

    struct StateInfo {
        uint64_t generationCount;
        uint32_t aliveCellCount;
    };

    [[nodiscard]] StateInfo state() const { return mStateInfo; }

    void update();

    void reset();

    void setState(const std::vector<glm::vec3>& state);

    void draw(glm::mat4 view, glm::mat4 projection);

private:
    void processNeighbors(Cell& cell);

    void checkNeighbor(Cell& currentAlive, glm::vec3 neighPos);

    StateInfo mStateInfo{};

    std::unordered_map<std::string, Cell> mAliveCells;
    std::vector<std::string> mCurrentDeadCellKeys;
    std::vector<Cell> mNeighboringDeadCells;
    std::vector<glm::vec3> mCurrentState;
};
