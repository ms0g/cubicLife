#pragma once

#include <vector>
#include <string>

namespace texture {
unsigned load(const char* path);

unsigned int loadCubemap(std::vector <std::string>& faces);
}
