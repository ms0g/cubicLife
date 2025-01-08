#include "core/engine.h"
#include "world/world.h"
#include "renderer/skybox.h"
#include "world/states.hpp"

int main(int argc, char** argv) {
    CAEngine cae;
    cae.init();

    World world{};
    world.setState(state::cube);

    cae.run(world);

    return 0;
}
