#include "core/engine.h"
#include "world/terrain.h"
#include "world/skybox.h"


int main() {
    VoxelEngine voxen;
    voxen.init();

    Terrain terrain;
    Skybox skyBox;

    voxen.run(terrain, skyBox);

    return 0;
}
