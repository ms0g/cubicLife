#include "cell.h"
#include "glm/gtc/matrix_transform.hpp"
#include "mesh/cellMesh.h"
#include "filesystem/filesystem.h"
#include "../shader/shader.h"

Cell::Cell(glm::vec3 pos) : mPos(pos) {
    mModelMat = glm::translate(mModelMat, mPos);
    mMesh = std::make_unique<CellMesh>(mVertices);
    mMesh->setup();
}

Cell::~Cell() = default;

Cell::Cell(Cell&& other) noexcept {
    mAliveNeighbors = other.mAliveNeighbors;
    mModelMat = other.mModelMat;
    mPos = other.mPos;
    mVertices = std::move(other.mVertices);
    mMesh = std::move(other.mMesh);
}

Cell& Cell::operator=(Cell&& other) noexcept {
    mAliveNeighbors = other.mAliveNeighbors;
    mModelMat = other.mModelMat;
    mPos = other.mPos;
    mVertices = std::move(other.mVertices);
    mMesh = std::move(other.mMesh);

    return *this;
}

void Cell::draw(glm::mat4 view, glm::mat4 projection, Shader& shader) {
    shader.activate();
    shader.setMat4("view", view);
    shader.setMat4("model", mModelMat);
    shader.setMat4("projection", projection);

    mMesh->render();
}




