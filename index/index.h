#pragma once

#include <string>
#include <unordered_map>

class Index {
private:
    std::unordered_map<std::string, std::string> entries;

public:
    void add(const std::string& path, const std::string& sha);
    void load();
    void save() const;

    const std::unordered_map<std::string, std::string>& get_entries() const;
};