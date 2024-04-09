#include "cell.h"
#include "mesh/cellMesh.h"
#include "glm/gtc/matrix_transform.hpp"
#include "filesystem/filesystem.h"
#include "../shader/shader.h"

std::vector<float> Cell::vertices = {
        // Back face
        -0.5f, -0.5f, -0.5f, // Bottom-left
         0.5f,  0.5f, -0.5f, // top-right
         0.5f, -0.5f, -0.5f, // bottom-right
         0.5f,  0.5f, -0.5f, // top-right
        -0.5f, -0.5f, -0.5f, // bottom-left
        -0.5f,  0.5f, -0.5f, // top-left
        // Front face
        -0.5f, -0.5f,  0.5f, // bottom-left
         0.5f, -0.5f,  0.5f, // bottom-right
         0.5f,  0.5f,  0.5f, // top-right
         0.5f,  0.5f,  0.5f, // top-right
        -0.5f,  0.5f,  0.5f, // top-left
        -0.5f, -0.5f,  0.5f, // bottom-left
        // Left face
        -0.5f,  0.5f,  0.5f, // top-right
        -0.5f,  0.5f, -0.5f, // top-left
        -0.5f, -0.5f, -0.5f, // bottom-left
        -0.5f, -0.5f, -0.5f, // bottom-left
        -0.5f, -0.5f,  0.5f, // bottom-right
        -0.5f,  0.5f,  0.5f, // top-right
        // Right face
         0.5f,  0.5f,  0.5f, // top-left
         0.5f, -0.5f, -0.5f, // bottom-right
         0.5f,  0.5f, -0.5f, // top-right
         0.5f, -0.5f, -0.5f, // bottom-right
         0.5f,  0.5f,  0.5f, // top-left
         0.5f, -0.5f,  0.5f, // bottom-left
        // Bottom face
        -0.5f, -0.5f, -0.5f, // top-right
         0.5f, -0.5f, -0.5f, // top-left
         0.5f, -0.5f,  0.5f, // bottom-left
         0.5f, -0.5f,  0.5f, // bottom-left
        -0.5f, -0.5f,  0.5f, // bottom-right
        -0.5f, -0.5f, -0.5f, // top-right
        // Top face
        -0.5f,  0.5f, -0.5f, // top-left
         0.5f,  0.5f,  0.5f, // bottom-right
         0.5f,  0.5f, -0.5f, // top-right
         0.5f,  0.5f,  0.5f, // bottom-right
        -0.5f,  0.5f, -0.5f, // top-left
        -0.5f,  0.5f,  0.5f, // bottom-left
};

std::unique_ptr<CellMesh> Cell::mesh = std::make_unique<CellMesh>(Cell::vertices);

bool Cell::meshCalled = false;

Cell::Cell(glm::vec3 pos) : mPos(pos) {
    mModelMat = glm::translate(mModelMat, mPos);

    if (!meshCalled) {
        mesh->setup();
        meshCalled = true;
    }
}

Cell::~Cell() = default;

Cell::Cell(Cell&& other) noexcept {
    mAliveNeighbors = other.mAliveNeighbors;
    mModelMat = other.mModelMat;
    mPos = other.mPos;
}

Cell& Cell::operator=(Cell&& other) noexcept {
    mAliveNeighbors = other.mAliveNeighbors;
    mModelMat = other.mModelMat;
    mPos = other.mPos;

    return *this;
}

void Cell::draw(glm::mat4 view, glm::mat4 projection, Shader& shader) {
    shader.activate();
    shader.setMat4("view", view);
    shader.setMat4("model", mModelMat);
    shader.setMat4("projection", projection);

    mesh->render();
}




