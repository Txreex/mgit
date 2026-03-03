#pragma once

#include <string>

class ObjectStore {
public:
    // Write raw object content using its SHA
    static void write(const std::string& sha,
                      const std::string& content);

    //check if object already exists
    static bool exists(const std::string& sha);
};