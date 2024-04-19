#include "filesystem/filesystem.h"
#include <filesystem>

std::string fs::path(const std::string& p) {
    auto cwd = std::filesystem::current_path().parent_path();
    //cwd.erase(cwd.find_last_of('/'));
    return cwd.append(p).string();
}
