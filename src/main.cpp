#include "engine/engine.h"


int main() {
    VoxelEngine voxEngine;

    voxEngine.init("suzanne.glb");
    voxEngine.run();

    return 0;
}
