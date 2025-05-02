#pragma once

#include <string>
#include "glm/glm.hpp"

namespace key {
inline std::string createFromPosition(const glm::vec3 pos) {
    return std::string(std::to_string(pos.x) + std::to_string(pos.y) + std::to_string(pos.z));
}
}
