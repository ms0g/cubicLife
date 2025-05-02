#pragma once

#include "glm/glm.hpp"

class Cell {
public:
    explicit Cell(glm::vec3 pos);

    Cell(const Cell& other);

    Cell& operator=(const Cell& other) = default;

    Cell(Cell&& other) noexcept;

    Cell& operator=(Cell&& other) noexcept;

    [[nodiscard]] int aliveNeighborsCount() const { return mAliveNeighbors; }

    [[nodiscard]] glm::vec3 pos() const { return mPos; }

    void resetAliveNeighbors() { mAliveNeighbors = 0; }

    void incAliveNeighbors() { mAliveNeighbors++; }

    bool operator==(const Cell& other) const {
        return abs(mPos.x - other.pos().x) < FLT_EPSILON &&
               abs(mPos.y - other.pos().y) < FLT_EPSILON &&
               abs(mPos.z - other.pos().z) < FLT_EPSILON;
    }

private:
    glm::vec3 mPos{};
    int mAliveNeighbors{0};
};
