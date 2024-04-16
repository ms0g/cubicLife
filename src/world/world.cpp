#include "world.h"
#include "glm/gtc/matrix_transform.hpp"
#include "cell.h"
#include "hash.hpp"
#include "mesh/cellMesh.h"
#include "filesystem/filesystem.h"
#include "../configs/configs.hpp"
#include "../shader/shader.h"

#define ADJ 1
#define MAX_CELL_NUM 500

World::World() {
    mMesh = std::make_unique<CellMesh>(mVertices);
    mMesh->setup();

    mShader = std::make_unique<Shader>(fs::path(SHADER_DIR + "cell.vert.glsl"),
                                       fs::path(SHADER_DIR + "cell.frag.glsl"));

    for (auto& pos: mCellPositions) {
        mAliveCells.emplace(hash::hasher(pos), Cell{pos});
    }
}

World::~World() = default;

void World::update() {
    if (mAliveCells.size() >= MAX_CELL_NUM) return;

    for (auto& cellPair: mAliveCells) {
        auto& cell = cellPair.second;

        for (int i = -1; i <= 1; ++i) {
            processNeighbors(cell, cell.pos().y + (float)i);
        }

        if (cell.pos().z >= ZFAR) {
            mCurrentDeadCellIndexes.push_back(cellPair.first);
            continue;
        }

        if (cell.aliveNeighborsCount() < 5 || cell.aliveNeighborsCount() > 6) {
            mCurrentDeadCellIndexes.push_back(cellPair.first);
        } else {
            cell.resetAliveNeighbors();
        }
    }

    for (auto& neighboringDeadCell: mNeighboringDeadCells) {
        if (neighboringDeadCell.aliveNeighborsCount() == 4) {
            neighboringDeadCell.resetAliveNeighbors();
            mAliveCells.emplace(hash::hasher(neighboringDeadCell.pos()), std::move(neighboringDeadCell));
        }
    }

    for (auto& index: mCurrentDeadCellIndexes) {
        auto it = mAliveCells.find(index);
        mAliveCells.erase(it);
    }

    mGenerationCount++;
    mState.aliveCellCount = mAliveCells.size();
    mState.generationCount = mGenerationCount;

    mNeighboringDeadCells.clear();
    mCurrentDeadCellIndexes.clear();
}

void World::draw(glm::mat4 view, glm::mat4 projection) {
    // Setup model matrices
    std::vector<glm::mat4> modelMatrices;
    for (auto& aliveCell: mAliveCells) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, aliveCell.second.pos());

        modelMatrices.push_back(model);
    }

    mMesh->setupInstancing(modelMatrices);

    mShader->activate();
    mShader->setMat4("view", view);
    mShader->setMat4("projection", projection);

    mMesh->render();
}

void World::processNeighbors(Cell& cell, float y) {
    // self
    glm::vec3 neighPos = {cell.pos().x, y, cell.pos().z};
    checkNeighbor(cell, neighPos);

    // right neighbor
    neighPos.x = cell.pos().x + ADJ;
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

    auto candidateCell = Cell{neighPos};
    if (currentAlive == candidateCell)
        return;

    uint64_t index = hash::hasher(neighPos);
    if (auto it = mAliveCells.find(index); it != mAliveCells.end()) {
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
