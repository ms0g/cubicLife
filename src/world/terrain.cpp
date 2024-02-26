#include "terrain.h"
#include <stdexcept>
#include <random>
#include "glm/gtc/matrix_transform.hpp"
#include "image/stb_image.h"


Terrain::Terrain() {
    int width, height, nrComponents;
    unsigned char* data = stbi_load(fs::path(ASSET_DIR + "heightmap.png").c_str(), &width, &height, &nrComponents, 0);

    if (!data) {
        stbi_image_free(data);
        throw std::runtime_error("Heightmap failed to load\n");
    }

    std::vector<glm::vec3> cubePositions;
    float yScale = 64.0f / 256.0f, yShift = 16.0f;  // apply a scale+shift to the height data

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // retrieve texel for (i,j) tex coord
            unsigned char* texel = &data[(j + width * i) * nrComponents];
            // raw height at coordinate
            unsigned char y = texel[0];

            cubePositions.emplace_back(glm::vec3{-height / 2.0f + height * i / (float) height,
                                                 (float) y * yScale - yShift,
                                                 -width / 2.0f + width * j / (float) width});
        }
    }
    stbi_image_free(data);

    std::vector<glm::mat4> modelMatrices;
    for (auto& pos: cubePositions) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, pos);

        modelMatrices.push_back(model);
    }

    m_cube = std::make_unique<Cube>(modelMatrices);
}

void Terrain::build(glm::mat4 view, glm::mat4 projection) {
    m_cube->updateViewMatrix(view);
    m_cube->updateProjectionMatrix(projection);
    m_cube->draw();
}
