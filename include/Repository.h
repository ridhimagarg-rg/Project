#pragma once
#include "StagingArea.h"
#include "CommitStore.h"
#include "BranchManager.h"
#include "Logger.h"
#include <string>

// ties everything together — one method per command
class Repository {
    std::string   root;
    StagingArea   stage;
    CommitStore   store;
    BranchManager branches;
    Logger        logger;

    void requireInit() const;

public:
    explicit Repository(const std::string& dir = ".");

    void cmdInit();
    void cmdAdd   (const std::string& file);
    void cmdCommit(const std::string& msg);
    void cmdLog   ()                          const;
    void cmdBranch(const std::string& name);
};
