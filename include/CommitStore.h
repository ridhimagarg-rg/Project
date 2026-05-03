#pragma once
#include "Commit.h"
#include <string>

// reads and writes commit objects under .minigit/objects/
class CommitStore {
    std::string objDir;

public:
    explicit CommitStore(const std::string& root);

    void   save(const Commit& c)              const;
    Commit load(const std::string& hash)      const;
    bool   has (const std::string& hash)      const;
};
