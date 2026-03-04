#include "commit.h"

#include "../index/index.h"
#include "../objects/tree.h"
#include "../objects/object_store.h"
#include "../hashing/sha1.h"

#include <fstream>
#include <map>
#include <iostream>

static std::string get_parent_commit(){
    std::ifstream head(".mgit/HEAD");

    if (!head)
        return "";

    std::string parent;
    head >> parent;

    return parent;
}

static std::string build_tree(const std::map<std::string,std::string>& entries){
    Tree tree;

    std::map<std::string, std::map<std::string,std::string>> subdirs;

    for (const auto& [path, sha] : entries){
        auto pos = path.find('/');

        if (pos == std::string::npos){
            tree.add_entry(path, sha, 100644);
        }else{
            std::string dir = path.substr(0, pos);
            std::string rest = path.substr(pos + 1);

            subdirs[dir][rest] = sha;
        }
    }

    for (const auto& [dir, files] : subdirs){
        std::string subtree_sha = build_tree(files);
        tree.add_entry(dir, subtree_sha, 40000);
    }

    return tree.store();
}

void commit(const std::string& message){
    Index index;
    index.load();

    auto entries = index.get_entries();

    if (entries.empty()){
        std::cout << "Nothing to commit\n";
        return;
    }

    std::map<std::string,std::string> ordered(entries.begin(), entries.end());
    std::string tree_sha = build_tree(ordered);
    std::string parent = get_parent_commit();
    std::string content = "tree " + tree_sha + "\n";

    if (!parent.empty())
        content += "parent " + parent + "\n";

    content += "message " + message + "\n";

    std::string serialized = "commit ";
    serialized += std::to_string(content.size());
    serialized.push_back('\0');
    serialized += content;

    std::string commit_sha = sha1(serialized);

    ObjectStore::write(commit_sha, serialized);

    std::ofstream head(".mgit/HEAD");
    head << commit_sha;

    std::cout << "Committed " << commit_sha << "\n";
}