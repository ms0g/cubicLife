#pragma once

#include <filesystem>
#include <string>

namespace fs {

inline std::string path(const std::string& p) {
    auto cwd = std::filesystem::current_path().parent_path();
    return cwd.append(p).string();
}
}
