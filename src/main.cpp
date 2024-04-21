#include "core/engine.h"
#include "world/world.h"
#include "world/skybox.h"
#include "world/states.hpp"

int main(int argc, char** argv) {
    CAEngine cae;
    cae.init();

    Skybox skyBox{};

    World world{};
    world.setState(states::cube);

    cae.run(world, skyBox);

    return 0;
}
