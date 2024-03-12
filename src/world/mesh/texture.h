#pragma once

#include <vector>
#include <string>

struct Texture {
    unsigned int id;
    std::string name;
    std::string path;
};

namespace texture {
unsigned load(const char* path);

unsigned int loadCubemap(std::vector <std::string>& faces);
}
