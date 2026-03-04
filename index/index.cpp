#include "index.h"

#include <unordered_map>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

void Index::add(const std::string& path, const std::string& sha) {
    entries[path] = sha;
}

void Index::load() {
    entries.clear();
    std::ifstream in(".mgit/index");
    if (!in) return;
    std::string path, sha;
    while (in >> path >> sha) {
        entries[path] = sha;
    }
}

void Index::save() const {
    fs::create_directories(".mgit");
    std::ofstream out(".mgit/index");
    for (const auto& [path, sha] : entries) {
        out << path << " " << sha << "\n";
    }
}

const std::unordered_map<std::string, std::string>& Index::get_entries() const {
    return entries;
}