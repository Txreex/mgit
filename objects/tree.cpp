#include "tree.h"
#include "../hashing/sha1.h"
#include "object_store.h"

#include <string>
#include <vector>
#include <algorithm>

TreeEntry::TreeEntry(const std::string &name, 
    const std::string & sha,
    int mode) 
    : name(name) , sha(sha) , mode(mode){}

void Tree::add_entry(const std::string& name,
                     const std::string& sha,
                     int mode)
{
    entries.emplace_back(name, sha, mode);
}

std::string Tree::serialize() const {
    std::string body;

    for (const auto& entry : entries) {
        body += std::to_string(entry.mode);
        body += " ";
        body += entry.name;
        body += " ";
        body += entry.sha;
        body += "\n";
    }

    std::string header = "tree ";
    header += std::to_string(body.size());
    header += '\0';

    return header + body;
}

std::string Tree::hash() const{
    return sha1(serialize());
}

std::string Tree::store(){
    ObjectStore::write(hash() , serialize());
    return hash();
}


