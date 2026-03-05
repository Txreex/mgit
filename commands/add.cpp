#include "add.h"

#include "../objects/blob.h"
#include "../index/index.h"

#include <filesystem>
#include <fstream>
#include <iterator>
#include <iostream>

namespace fs = std::filesystem;

static std::string read_file(const std::string& path)
{
    std::ifstream in(path, std::ios::binary);

    if (!in)
        throw std::runtime_error("Failed to open file");

    return std::string(
        (std::istreambuf_iterator<char>(in)),
        std::istreambuf_iterator<char>()
    );
}

void add_file(const std::string& path)
{
    Index index;
    index.load();

    if (fs::is_regular_file(path))
    {
        std::string content = read_file(path);

        Blob blob(content);
        std::string sha = blob.store();

        index.add(path, sha);
    }

    else if (fs::is_directory(path))
    {
        for (auto it = fs::recursive_directory_iterator(path);
             it != fs::recursive_directory_iterator(); ++it)
        {
            if (it->path().filename() == ".mgit")
            {
                it.disable_recursion_pending();
                continue;
            }

            if (!fs::is_regular_file(*it))
                continue;

            std::string file = it->path().string();

            std::string content = read_file(file);

            Blob blob(content);
            std::string sha = blob.store();

            index.add(file, sha);

            std::cout << "Added " << file << "\n";
        }
    }

    index.save();
}