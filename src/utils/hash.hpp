#pragma once

#include <bit>
#include "glm/glm.hpp"

namespace hash {
/**
 * hash(x,y,z) = ( x * p1 xor y * p2 xor z * p3)
 * p1, p2, p3 are large prime numbers from
 * http://www.beosil.com/download/CollisionDetectionHashing_VMV03.pdf
 */
uint64_t hasher(const glm::vec3 pos) {
    uint64_t hashCode = 0;
    hashCode ^= (std::bit_cast<uint32_t>(pos.x) * 73856093);
    hashCode ^= (std::bit_cast<uint32_t>(pos.y) * 19349663);
    hashCode ^= (static_cast<uint64_t>(pos.z) * 83492791);
    return hashCode;
}
}
