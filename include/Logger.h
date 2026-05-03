#pragma once
#include "CommitStore.h"
#include "BranchManager.h"

// just walks the parent chain and prints stuff
class Logger {
    const CommitStore&   store;
    const BranchManager& bm;

public:
    Logger(const CommitStore& cs, const BranchManager& b);
    void show() const;
};
