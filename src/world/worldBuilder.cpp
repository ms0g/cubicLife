#include "worldBuilder.h"
#include <random>
#include "glm/gtc/matrix_transform.hpp"

WorldBuilder::WorldBuilder() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10);

    for (int x = 10; x > 0; --x) {
        float xPos = x + 15;
        float yPos = dis(gen);
        for (int z = 10; z > 0; --z) {
            cubePositions.emplace_back(glm::vec3{xPos, yPos, z});
            yPos--;
        }
    }
}

void WorldBuilder::build(glm::mat4 view, glm::mat4 projection) {
    m_cube.updateViewMatrix(view);
    m_cube.updateProjectionMatrix(projection);

    for (auto& pos: cubePositions) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, pos);

        m_cube.updateModelMatrix(model);

        m_cube.draw();
    }
}
