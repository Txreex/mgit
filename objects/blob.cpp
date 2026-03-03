#include "blob.h"
#include "../hashing/sha1.h"
#include "object_store.h"

#include <string>

Blob::Blob(const std::string& content){
    this->content = content;
}

std::string Blob::serialize() const{
    std::string res = "blob ";
    int size = content.size();
    res += std::to_string(size) + '\0' + content;
    return res;
}

std::string Blob::hash() const{
    return sha1(serialize());
}

std::string Blob::store() const{
    ObjectStore::write(hash() , serialize());
    return hash();
}