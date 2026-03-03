#include "objects/tree.h"
#include "objects/blob.h"
#include <iostream>

int main() {
    Blob b("hello");
    std::string blob_sha = b.store();

    Tree t;
    t.add_entry("file.txt", blob_sha, 100644);

    std::string tree_sha = t.store();

    std::cout << "Tree SHA: " << tree_sha << "\n";
}