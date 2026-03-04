#include "commands/init.h"
#include "commands/add.h"
#include "commands/commit.h"
#include "repo/repository.h"

#include <iostream>
#include <unordered_map>
#include <functional>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: mgit <command>\n";
        return 1;
    }

    std::string command = argv[1];

    std::unordered_map<std::string, std::function<void()>> commands;

    commands["init"] = []() {
        init_repo();
    };

    commands["add"] = [&]() {
        if (!is_repo())
        {
            std::cout << "Not an mgit repository\n";
            return;
        }

        if (argc < 3)
        {
            std::cout << "Specify file or folder\n";
            return;
        }

        add_file(argv[2]);
    };

    commands["commit"] = [&]() {
        if (!is_repo())
        {
            std::cout << "Not an mgit repository\n";
            return;
        }

        if (argc < 3)
        {
            std::cout << "Specify commit message\n";
            return;
        }

        commit(argv[2]);
    };

    if (commands.count(command))
        commands[command]();
    else
        std::cout << "Unknown command\n";

    return 0;
}