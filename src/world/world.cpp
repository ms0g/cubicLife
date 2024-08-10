#include "world.h"
#include "glm/gtc/matrix_transform.hpp"
#include "cell.h"
#include "mesh/cellMesh.h"
#include "../utils/key.hpp"
#include "../core/shader.h"

#define MAX_CELL_NUM 2000

World::World() {
    mMesh = std::make_unique<CellMesh>(mVertices, mTextures);
    mMesh->setup();

    mShader = std::make_unique<Shader>(fs::path(SHADER_DIR + "/cell.vert"),
                                       fs::path(SHADER_DIR + "/cell.frag"));

    mShader->activate();
    mShader->setInt(mTextures[0].name, 0);
}

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

void World::setState(std::vector<glm::vec3>& state) {
    if (mCurrentState != state)
        mCurrentState = std::move(state);

    for (auto& pos: mCurrentState) {
        mAliveCells.emplace(key::createFromPosition(pos), Cell{pos});
    }
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
