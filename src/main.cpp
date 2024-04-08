#include "core/engine.h"
#include "world/world.h"
#include "world/skybox.h"

int main() {
    CAEngine cae;
    cae.init();

    World world{};
    Skybox skyBox{};

    cae.run(world, skyBox);

    return 0;
}
