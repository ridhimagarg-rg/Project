#include "BranchManager.h"
#include "Utils.h"

#include <filesystem>
#include <iostream>
#include <stdexcept>

namespace fs = std::filesystem;

BranchManager::BranchManager(const std::string& root)
    : refsDir (root + "/.minigit/refs/heads/"),
      headFile(root + "/.minigit/HEAD") {}

void BranchManager::setup() {
    fs::create_directories(refsDir);
    writeFile(headFile, "ref: refs/heads/main\n");
}

std::string BranchManager::current() const {
    auto content = readFile(headFile);
    auto slash   = content.rfind('/');
    if (slash == std::string::npos)
        throw std::runtime_error("HEAD is broken");

    auto name = content.substr(slash + 1);
    while (!name.empty() && (name.back() == '\n' || name.back() == '\r'))
        name.pop_back();
    return name;
}

std::string BranchManager::tip(const std::string& branch) const {
    auto path = refsDir + branch;
    if (!pathExists(path)) return "";
    auto h = readFile(path);
    while (!h.empty() && (h.back() == '\n' || h.back() == '\r'))
        h.pop_back();
    return h;
}

void BranchManager::setTip(const std::string& branch, const std::string& hash) {
    writeFile(refsDir + branch, hash + "\n");
}

bool BranchManager::exists(const std::string& branch) const {
    return pathExists(refsDir + branch);
}

void BranchManager::create(const std::string& branch) {
    if (exists(branch))
        throw std::runtime_error("branch already exists: " + branch);

    auto cur  = current();
    auto head = tip(cur);

    // new branch starts at the same commit as current
    writeFile(refsDir + branch, head.empty() ? "" : head + "\n");

    std::cout << "created branch '" << branch << "'";
    if (!head.empty())
        std::cout << " -> " << head.substr(0, 8);
    std::cout << "\n";
}

void BranchManager::list() const {
    auto cur = current();
    for (const auto& e : fs::directory_iterator(refsDir)) {
        auto name = e.path().filename().string();
        std::cout << (name == cur ? "* " : "  ") << name << "\n";
    }
}
