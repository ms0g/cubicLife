#include "world.h"
#include "cell.h"
#include "../utils/key.hpp"

#define MAX_CELL_NUM 2000

World::World() = default;

World::~World() = default;

void World::update() {
    if (mAliveCells.size() >= MAX_CELL_NUM) return;

    for (auto& cellPair: mAliveCells) {
        auto& cell = cellPair.second;

        processNeighbors(cell);

        if (cell.pos().z >= ZFAR) {
            mCurrentDeadCellKeys.push_back(cellPair.first);
            continue;
        }

        if (cell.aliveNeighborsCount() < 5 || cell.aliveNeighborsCount() > 6) {
            mCurrentDeadCellKeys.push_back(cellPair.first);
        } else {
            cell.resetAliveNeighbors();
        }
    }

    for (auto& neighboringDeadCell: mNeighboringDeadCells) {
        if (neighboringDeadCell.aliveNeighborsCount() == 4) {
            neighboringDeadCell.resetAliveNeighbors();
            mAliveCells.emplace(key::createFromPosition(neighboringDeadCell.pos()), std::move(neighboringDeadCell));
        }
    }

    for (auto& index: mCurrentDeadCellKeys) {
        auto it = mAliveCells.find(index);
        mAliveCells.erase(it);
    }

    mStateInfo.aliveCellCount = mAliveCells.size();
    mStateInfo.generationCount++;

    mNeighboringDeadCells.clear();
    mCurrentDeadCellKeys.clear();
}

void World::reset() {
    mAliveCells.clear();
    mStateInfo = {0};
    setState(mCurrentState);
}

void World::setState(const std::vector<glm::vec3>& state) {
    if (mCurrentState != state)
        mCurrentState = state;

    for (auto& pos: mCurrentState) {
        mAliveCells.emplace(key::createFromPosition(pos), Cell{pos});
    }
}

void World::processNeighbors(Cell& cell) {
    for (int i = -1; i < 2; ++i) {
        for (int j = -1; j < 2; ++j) {
            for (int k = -1; k < 2; ++k) {
                glm::vec3 neighPos = {cell.pos().x + i, cell.pos().y + j, cell.pos().z + k};
                checkNeighbor(cell, neighPos);
            }
        }
    }
}

void World::checkNeighbor(Cell& currentAlive, glm::vec3 neighPos) {
    bool found = false;

    auto candidateCell = Cell{neighPos};
    if (currentAlive == candidateCell)
        return;

    if (auto it = mAliveCells.find(key::createFromPosition(neighPos)); it != mAliveCells.end()) {
        currentAlive.incAliveNeighbors();
        found = true;
    }

    if (!found) {
        for (auto& neighboringDeadCell: mNeighboringDeadCells) {
            if (neighboringDeadCell == candidateCell) {
                found = true;
                neighboringDeadCell.incAliveNeighbors();
                break;
            }
        }
        if (!found) {
            candidateCell.incAliveNeighbors();
            mNeighboringDeadCells.emplace_back(std::move(candidateCell));
        }
    }
}
