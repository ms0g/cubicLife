#pragma once

#include <vector>
#include <memory>
#include "glm/glm.hpp"

class Shader;
class CellMesh;
class Cell {
public:
    explicit Cell(glm::vec3 pos);

    ~Cell();

    Cell(Cell&& other) noexcept;

    Cell& operator=(Cell&& other) noexcept;

    [[nodiscard]] int aliveNeighborsCount() const { return mAliveNeighbors; }

    [[nodiscard]] glm::vec3 pos() const { return mPos; }

    void resetAliveNeighbors() { mAliveNeighbors = 0;}

    void incAliveNeighbors() { mAliveNeighbors++; }

    void draw(glm::mat4 view, glm::mat4 projection, Shader& shader);

    bool operator==(const Cell &other) const {
        return (mPos.x == other.mPos.x && mPos.y == other.mPos.y && mPos.z == other.mPos.z) ;
    }

private:
    int mAliveNeighbors{0};

    glm::vec3 mPos{};
    glm::mat4 mModelMat{1.0f};

    static std::unique_ptr<CellMesh> mesh;
    static std::vector<float> vertices;
    static bool meshCalled;
};
