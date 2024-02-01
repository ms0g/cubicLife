#include "cube.h"
#include "../shader/shader.h"

Cube::Cube(Shader& shader) {
    shader.activate();
    shader.setInt(textures[0].name, 0);
    shader.setInt(textures[1].name, 1);

    mesh.setup(vertices, textures);
}

void Cube::draw() {
    mesh.render();
}
