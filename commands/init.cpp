#include "init.h"

#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

void init_repo()
{
    if (fs::exists(".mgit"))
    {
        std::cout << "Repository already exists\n";
        return;
    }

    fs::create_directory(".mgit");
    fs::create_directory(".mgit/objects");

    std::ofstream(".mgit/index");   // create empty index
    std::ofstream(".mgit/HEAD");    // empty head

    std::cout << "Initialized empty mgit repository\n";
}