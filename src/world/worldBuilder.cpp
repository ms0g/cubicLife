#include "worldBuilder.h"
#include "glm/gtc/matrix_transform.hpp"

glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)
};

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
