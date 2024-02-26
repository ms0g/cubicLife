#include "core/engine.h"
#include "world/terrain.h"


int main() {
    VoxelEngine voxen;
    voxen.init();

    Terrain terrain;

    voxen.run(terrain);

    return 0;
}
