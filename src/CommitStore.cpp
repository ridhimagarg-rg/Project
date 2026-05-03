#include "CommitStore.h"
#include "Utils.h"
#include <stdexcept>

CommitStore::CommitStore(const std::string& root)
    : objDir(root + "/.minigit/objects/") {}

void CommitStore::save(const Commit& c) const {
    writeFile(objDir + "commit_" + c.hash, c.serialize());
}

Commit CommitStore::load(const std::string& hash) const {
    auto path = objDir + "commit_" + hash;
    if (!pathExists(path))
        throw std::runtime_error("no such commit: " + hash);
    return Commit::deserialize(readFile(path));
}

bool CommitStore::has(const std::string& hash) const {
    return !hash.empty() && pathExists(objDir + "commit_" + hash);
}
