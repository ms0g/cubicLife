#pragma once

#include <vector>
#include <string>
#include "glad/glad.h"

struct Texture {
    GLuint id;
    std::string name;
    std::string path;
};

namespace texture {
GLuint load(const char* path);

GLuint loadCubemap(std::vector <std::string>& faces);
}
