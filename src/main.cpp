#include "core/engine.h"
#include "world/world.h"
#include "world/skybox.h"

int main() {
    CellularAutomatonEngine cae;
    cae.init();

    World world;
    Skybox skyBox;

    cae.run(world, skyBox);

    return 0;
}
