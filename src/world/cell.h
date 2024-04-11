#pragma once

#include <vector>
#include <memory>
#include "glm/glm.hpp"

class Cell {
public:
    explicit Cell(glm::vec3 pos);

    Cell(Cell&& other) noexcept;

    Cell& operator=(Cell&& other) noexcept;

    [[nodiscard]] int aliveNeighborsCount() const { return mAliveNeighbors; }

    [[nodiscard]] glm::vec3 pos() const { return mPos; }

    void resetAliveNeighbors() { mAliveNeighbors = 0;}

    void incAliveNeighbors() { mAliveNeighbors++; }

    bool operator==(const Cell &other) const {
        return (mPos.x == other.pos().x && mPos.y == other.pos().y && mPos.z == other.pos().z) ;
    }

private:
    glm::vec3 mPos{};
    int mAliveNeighbors{0};
};
