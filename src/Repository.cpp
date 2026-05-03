#include "Repository.h"
#include "Utils.h"

#include <filesystem>
#include <iostream>
#include <stdexcept>

namespace fs = std::filesystem;

Repository::Repository(const std::string& dir)
    : root    (dir),
      stage   (dir),
      store   (dir),
      branches(dir),
      logger  (store, branches)
{}

void Repository::requireInit() const {
    if (!pathExists(root + "/.minigit"))
        throw std::runtime_error("not a minigit repo — run 'minigit init' first");
}

void Repository::cmdInit() {
    if (pathExists(root + "/.minigit")) {
        std::cout << "already initialised\n";
        return;
    }
    fs::create_directories(root + "/.minigit/objects");
    branches.setup();
    writeFile(root + "/.minigit/INDEX", "");
    std::cout << "initialised repo in " << fs::absolute(root + "/.minigit") << "\n";
}

void Repository::cmdAdd(const std::string& file) {
    requireInit();
    stage.stage(file);
}

void Repository::cmdCommit(const std::string& msg) {
    requireInit();

    if (msg.empty())
        throw std::runtime_error("commit message can't be empty");
    if (stage.empty())
        throw std::runtime_error("nothing staged — use 'add' first");

    auto branch = branches.current();
    auto parent = branches.tip(branch);
    auto tree   = stage.snapshot();

    Commit c;
    c.parent  = parent;
    c.message = msg;
    c.when    = getTimestamp();
    c.branch  = branch;
    c.tree    = tree;
    c.hash    = hashContent(parent + msg + c.when + tree);

    store.save(c);
    branches.setTip(branch, c.hash);
    stage.clear();

    std::cout << "[" << branch << " " << c.hash.substr(0, 8) << "] " << msg << "\n";
}

void Repository::cmdLog() const {
    requireInit();
    logger.show();
}

void Repository::cmdBranch(const std::string& name) {
    requireInit();
    if (name.empty())
        branches.list();
    else
        branches.create(name);
}
