#include "object_store.h"

#include <filesystem>
#include <fstream>
#include <stdexcept>

namespace fs = std::filesystem;

void ObjectStore::write(const std::string& sha,
                        const std::string& content)
{
    if (sha.size() < 2) {
        throw std::runtime_error("Invalid SHA");
    }

    std::string folder = sha.substr(0, 2);
    std::string filename = sha.substr(2);

    fs::path base = ".mgit/objects";
    fs::path object_folder = base / folder;
    fs::path object_path = object_folder / filename;

    if (fs::exists(object_path)) {
        return;
    }

    fs::create_directories(object_folder);

    std::ofstream out(object_path, std::ios::binary);
    if (!out) {
        throw std::runtime_error("Failed to write object");
    }

    out.write(content.c_str(), content.size());
    out.close();
}

bool ObjectStore::exists(const std::string& sha)
{
    if (sha.size() < 2) {
        return false;
    }

    std::string folder = sha.substr(0, 2);
    std::string filename = sha.substr(2);

    fs::path base = ".mgit/objects";
    fs::path object_path = base / folder / filename;

    return fs::exists(object_path);
}