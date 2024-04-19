#include "core/engine.h"
#include "world/world.h"
#include "world/skybox.h"

const std::vector<glm::vec3> initialState = {
        {0.0f,   0.0f,  0.0f},
        {1.0f,   0.0f,  0.0f},
        {2.0f,   0.0f,  0.0f},
        {0.0f,   0.0f,  1.0f},
        {1.0f,   0.0f,  1.0f},
        {2.0f,   0.0f,  1.0f},
        {0.0f,   0.0f,  2.0f},
        {1.0f,   0.0f,  2.0f},
        {2.0f,   0.0f,  2.0f},

        {0.0f,   1.0f,  0.0f},
        {1.0f,   1.0f,  0.0f},
        {2.0f,   1.0f,  0.0f},
        {0.0f,   1.0f,  1.0f},
        {1.0f,   1.0f,  1.0f},
        {2.0f,   1.0f,  1.0f},
        {0.0f,   1.0f,  2.0f},
        {1.0f,   1.0f,  2.0f},
        {2.0f,   1.0f,  2.0f},

        {0.0f,  -1.0f,  0.0f},
        {1.0f,  -1.0f,  0.0f},
        {2.0f,  -1.0f,  0.0f},
        {0.0f,  -1.0f,  1.0f},
        {1.0f,  -1.0f,  1.0f},
        {2.0f,  -1.0f,  1.0f},
        {0.0f,  -1.0f,  2.0f},
        {1.0f,  -1.0f,  2.0f},
        {2.0f,  -1.0f,  2.0f},
};

int main(int argc, char **argv) {
    CAEngine cae;
    cae.init();

    Skybox skyBox{};
    World world{initialState};

    cae.run(world, skyBox);

    return 0;
}
