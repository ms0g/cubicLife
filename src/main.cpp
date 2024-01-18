#include "engine/engine.h"


int main() {
    Engine glEngine;
    glEngine.init("suzanne.glb");

    while (glEngine.isRunning()) {
        glEngine.processInput();
        glEngine.update();
        glEngine.render();
    }

    return 0;
}
