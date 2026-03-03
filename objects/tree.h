#include<string>
#include<vector>

class TreeEntry {
public:
    std::string name;
    std::string sha;
    int mode;

    TreeEntry(const std::string& name,
              const std::string& sha,
              int mode);
};

class Tree {
private:
    std::vector<TreeEntry> entries;

public:
    void add_entry(const std::string& name,
                   const std::string& sha,
                   int mode);

    std::string serialize() const;
    std::string hash() const;
    std::string store();
};