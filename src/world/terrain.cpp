#include "terrain.h"
#include <stdexcept>
#include <random>
#include "glm/gtc/matrix_transform.hpp"
#include "image/stb_image.h"
#include "filesystem/filesystem.h"
#include "cube.h"

Terrain::Terrain() : mCube(std::make_unique<Cube>()) {}

Terrain::~Terrain() = default;

void Terrain::build(glm::mat4 view, glm::mat4 modelMat, glm::mat4 projection) {
    mCube->update(view, modelMat, projection);
    mCube->draw();
}
