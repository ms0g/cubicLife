#include "engine/engine.h"
#include "world/worldBuilder.h"


int main() {
    VoxelEngine voxEngine;
    voxEngine.init();

    WorldBuilder worldBuilder;

    voxEngine.run(worldBuilder);

    return 0;
}
