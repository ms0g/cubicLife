#include "cell.h"

Cell::Cell(const glm::vec3 pos) : mPos(pos) {}

Cell::Cell(const Cell& other) {
    mPos = other.mPos;
    mAliveNeighbors = other.mAliveNeighbors;
}

Cell::Cell(Cell&& other) noexcept {
    mAliveNeighbors = other.mAliveNeighbors;
    mPos = other.mPos;
}

Cell& Cell::operator=(Cell&& other) noexcept {
    mAliveNeighbors = other.mAliveNeighbors;
    mPos = other.mPos;

    return *this;
}




