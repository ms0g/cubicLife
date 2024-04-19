#pragma once

#include <string>
#include "glm/glm.hpp"

namespace key {
std::string createFromPosition(const glm::vec3 pos) {
    return std::string(std::to_string(pos.x) + (char)pos.y + (char)pos.z);
}
}
