#include "world.h"
#include "glm/gtc/matrix_transform.hpp"
#include "cell.h"
#include "mesh/cellMesh.h"
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

World::World() {
    mMesh = std::make_unique<CellMesh>(mVertices);
    mMesh->setup();

    mShader = std::make_unique<Shader>(fs::path(SHADER_DIR + "cell.vert.glsl"),
                                       fs::path(SHADER_DIR + "cell.frag.glsl"));

    for (auto& pos: mCellPositions) {
        mAliveCells.emplace(kv::getIndex(), Cell{pos});
    }
}

World::~World() = default;

void World::update() {
    for (auto& cellPair: mAliveCells) {
        auto& cell = cellPair.second;

        processNeighbors(cell);

        if (cell.pos().z >= ZFAR) {
            mCurrentDeadCellIndexes.push_back(cellPair.first);
            continue;
        }

        if (cell.aliveNeighborsCount() < 2 || cell.aliveNeighborsCount() > 3) {
            mCurrentDeadCellIndexes.push_back(cellPair.first);
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

    // Setup model matrices
    std::vector<glm::mat4> modelMatrices;
    for (auto& aliveCell: mAliveCells) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, aliveCell.second.pos());

        modelMatrices.push_back(model);
    }

    mMesh->setupInstancing(modelMatrices);

    mGenerationCount++;
    mState.aliveCellCount = mAliveCells.size();
    mState.generationCount = mGenerationCount;

    mNeighboringDeadCells.clear();
    mCurrentDeadCellIndexes.clear();
}

void World::draw(glm::mat4 view, glm::mat4 projection) {
    mShader->activate();
    mShader->setMat4("view", view);
    mShader->setMat4("projection", projection);

    mMesh->render();
}

void World::processNeighbors(Cell& cell) {
    // right neighbor
    glm::vec3 neighPos = {cell.pos().x + ADJ, 0.0, cell.pos().z};
    checkNeighbor(cell, neighPos);

    // left neighbor
    neighPos.x = cell.pos().x - ADJ;
    checkNeighbor(cell, neighPos);

    // forward neighbor
    neighPos.x = cell.pos().x;
    neighPos.z = cell.pos().z - ADJ;
    checkNeighbor(cell, neighPos);

    // backward neighbor
    neighPos.z = cell.pos().z + ADJ;
    checkNeighbor(cell, neighPos);

    // forward right neighbor
    neighPos.x = cell.pos().x + ADJ;
    neighPos.z = cell.pos().z - ADJ;
    checkNeighbor(cell, neighPos);

    // forward left neighbor
    neighPos.x = cell.pos().x - ADJ;
    neighPos.z = cell.pos().z - ADJ;
    checkNeighbor(cell, neighPos);

    // backward right neighbor
    neighPos.x = cell.pos().x + ADJ;
    neighPos.z = cell.pos().z + ADJ;
    checkNeighbor(cell, neighPos);

    // backward left neighbor
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
