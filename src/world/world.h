#pragma once

#include <future>
#include <vector>
#include <unordered_map>
#include "glm/glm.hpp"
#include "../core/io.hpp"

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

    std::unordered_map<std::string, Cell>& aliveCells() { return mAliveCells; }

    void update();

    void reset();

    void setState(const std::vector<glm::vec3>& state);

private:
    void processNeighbors(Cell& cell);

    void checkNeighbor(Cell& currentAlive, glm::vec3 neighPos);

    StateInfo mStateInfo{};

    std::mutex mMutex;
    std::vector<std::future<void>> mFutures;

    std::unordered_map<std::string, Cell> mAliveCells;
    std::vector<std::string> mCurrentDeadCellKeys;
    std::vector<Cell> mNeighboringDeadCells;
    std::vector<glm::vec3> mCurrentState;
};
