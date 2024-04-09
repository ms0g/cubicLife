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

World::World() :
        mShader(std::make_unique<Shader>(fs::path(SHADER_DIR + "cell.vert.glsl"),
                                         fs::path(SHADER_DIR + "cell.frag.glsl"))) {
    for (auto& pos: cellPositions) {
        mAliveCells.emplace(kv::getIndex(), Cell{pos});
    }
}

World::~World() = default;

void World::update() {
    for (auto& cellPair: mAliveCells) {
        auto& cell = cellPair.second;

        processNeighbors(cell);

        if (cell.pos().z >= 300) {
            mCurrentDeadCellIndexes.insert(cellPair.first);
            continue;
        }

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
        cell.draw(view, projection, *mShader);
    }
}

void World::processNeighbors(Cell& cell) {
    // right neighbor
    glm::vec3 neighPos = {cell.pos().x + ADJ, 0.0, cell.pos().z};
    checkNeighbor(cell, neighPos);

    // left neighbor
    neighPos.x = cell.pos().x - ADJ;
    checkNeighbor(cell, neighPos);

    // top neighbor
    neighPos.x = cell.pos().x;
    neighPos.z = cell.pos().z - ADJ;
    checkNeighbor(cell, neighPos);

    // bottom neighbor
    neighPos.z = cell.pos().z + ADJ;
    checkNeighbor(cell, neighPos);

    // top right neighbor
    neighPos.x = cell.pos().x + ADJ;
    neighPos.z = cell.pos().z - ADJ;
    checkNeighbor(cell, neighPos);

    // top left neighbor
    neighPos.x = cell.pos().x - ADJ;
    neighPos.z = cell.pos().z - ADJ;
    checkNeighbor(cell, neighPos);

    // bottom right neighbor
    neighPos.x = cell.pos().x + ADJ;
    neighPos.z = cell.pos().z + ADJ;
    checkNeighbor(cell, neighPos);

    // bottom left neighbor
    neighPos.x = cell.pos().x - ADJ;
    neighPos.z = cell.pos().z + ADJ;
    checkNeighbor(cell, neighPos);
}

void World::checkNeighbor(Cell& currentAlive, glm::vec3 neighPos) {
    bool found = false;

    for (auto& cellPair: mAliveCells) {
        auto& aliveCell = cellPair.second;

        if ((aliveCell.pos().x == neighPos.x) &&
            (aliveCell.pos().z == neighPos.z)) {
            found = true;
            currentAlive.incAliveNeighbors();
            break;
        }
    }
    if (!found) {
        for (auto& neighboringDeadCell: mNeighboringDeadCells) {
            if ((neighboringDeadCell.pos().x == neighPos.x) &&
                (neighboringDeadCell.pos().z == neighPos.z)) {
                found = true;
                neighboringDeadCell.incAliveNeighbors();
                break;
            }
        }
        if (!found) {
            auto neighDeadCell = Cell{neighPos};
            neighDeadCell.incAliveNeighbors();
            mNeighboringDeadCells.emplace_back(std::move(neighDeadCell));
        }
    }
}
