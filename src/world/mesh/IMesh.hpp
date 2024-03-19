#pragma once

#include <vector>

class IMesh {
public:
    explicit IMesh(std::vector<float>& vertices) :
            mVertices(std::move(vertices)) {}

    virtual ~IMesh() = default;

    virtual void setup() = 0;

    virtual void render() = 0;

protected:
    unsigned int m_VAO{};
    unsigned int m_VBO{};
    // mesh Data
    std::vector<float> mVertices;
};
