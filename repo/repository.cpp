#include "repository.h"
#include <filesystem>

namespace fs = std::filesystem;

bool is_repo()
{
    return fs::exists(".mgit") && fs::is_directory(".mgit");
}