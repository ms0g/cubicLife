#include "core/engine.h"
#include "world/world.h"
#include "world/skybox.h"


int main() {
    VoxelEngine voxen;
    voxen.init();

    World world;
    Skybox skyBox;

    voxen.run(world, skyBox);

    return 0;
}
