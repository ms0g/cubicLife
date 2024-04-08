#include "world.h"
#include "cell.h"
#include "filesystem/filesystem.h"
#include "../configs/configs.hpp"
#include "../shader/shader.h"

#define ADJ 1

namespace kv {

static int index;

int getIndex() {
    return index++;
}
}

World::World() : mShader(std::make_unique<Shader>(fs::path(SHADER_DIR + "cube.vert.glsl"),
                                                  fs::path(SHADER_DIR + "cube.frag.glsl"))) {
    for (auto& pos: cellPositions) {
        mAliveCells.emplace(kv::getIndex(), Cell{pos});
    }
}

World::~World() = default;

void World::update() {
    for (auto& cellPair: mAliveCells) {
        auto& cell = cellPair.second;

        findAliveNeighbors(cell);

        if (cell.aliveNeighborsCount() < 2 || cell.aliveNeighborsCount() > 3) {
            mCurrentDeadCellIndexes.insert(cellPair.first);
        } else {
            cell.resetAliveNeighbors();
        }
    }

    for (auto& neighboringDeadCell: mNeighboringDeadCells) {
        if (neighboringDeadCell.aliveNeighborsCount() == 3) {
            neighboringDeadCell.resetAliveNeighbors();
            mAliveCells.emplace(kv::getIndex(), std::move(neighboringDeadCell));
        }
    }

    for (auto& index: mCurrentDeadCellIndexes) {
        auto it = mAliveCells.find(index);
        mAliveCells.erase(it);
    }

    mNeighboringDeadCells.clear();
    mCurrentDeadCellIndexes.clear();
}

void World::draw(glm::mat4 view, glm::mat4 projection) {
    for (auto& cellPair: mAliveCells) {
        auto& cell = cellPair.second;
        cell.update(view, projection, *mShader);
        cell.draw();
    }
}

void World::findAliveNeighbors(Cell& cell) {
    // right neighbor
    glm::vec3 neighPos = {cell.mPos.x + ADJ, 0.0, cell.mPos.z};
    Cell neigh{neighPos};

    checkIf(cell, neigh);

    // left neighbor
    neigh.mPos.x = cell.mPos.x - ADJ;
    checkIf(cell, neigh);

    // top neighbor
    neigh.mPos.x = cell.mPos.x;
    neigh.mPos.z = cell.mPos.z - ADJ;
    checkIf(cell, neigh);

    // bottom neighbor
    neigh.mPos.z = cell.mPos.z + ADJ;
    checkIf(cell, neigh);

    // top right neighbor
    neigh.mPos.x = cell.mPos.x + ADJ;
    neigh.mPos.z = cell.mPos.z - ADJ;
    checkIf(cell, neigh);

    // top left neighbor
    neigh.mPos.x = cell.mPos.x - ADJ;
    neigh.mPos.z = cell.mPos.z - ADJ;
    checkIf(cell, neigh);

    // bottom right neighbor
    neigh.mPos.x = cell.mPos.x + ADJ;
    neigh.mPos.z = cell.mPos.z + ADJ;
    checkIf(cell, neigh);

    // bottom left neighbor
    neigh.mPos.x = cell.mPos.x - ADJ;
    neigh.mPos.z = cell.mPos.z + ADJ;
    checkIf(cell, neigh);
}

void World::checkIf(Cell& currentAlive, Cell& neigh) {
    bool found = false;

    for (auto& aliveCell: mAliveCells) {
        if (aliveCell.second == neigh) {
            found = true;
            currentAlive.incAliveNeighbors();
            break;
        }
    }
    if (!found) {
        for (auto& neighboringDeadCell: mNeighboringDeadCells) {
            if (neighboringDeadCell == neigh) {
                found = true;
                neighboringDeadCell.incAliveNeighbors();
                break;
            }
        }
        if (!found) {
            auto neighDeadCell = Cell{glm::vec3(neigh.mPos.x, neigh.mPos.y, neigh.mPos.z)};
            neighDeadCell.incAliveNeighbors();
            mNeighboringDeadCells.emplace_back(std::move(neighDeadCell));
        }
        neigh.resetAliveNeighbors();
    }
}
