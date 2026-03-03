#pragma once

#include <string>

class Blob {
private:
    std::string content;

public:
    Blob(const std::string& content);

    std::string serialize() const;
    std::string hash() const;
    std::string store() const;
};