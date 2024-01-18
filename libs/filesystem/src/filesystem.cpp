#include "filesystem/filesystem.h"
#include <filesystem>

std::string Filesystem::path(const std::string& p) {
    auto cwd = std::filesystem::current_path().string();
    cwd.erase(cwd.find_last_of('/'));
    return cwd + "/" + p;
}
