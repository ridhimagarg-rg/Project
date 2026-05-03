#pragma once
#include <string>

// manages HEAD and all branch refs
//
// HEAD  ->  .minigit/HEAD           contains "ref: refs/heads/<branch>"
// refs  ->  .minigit/refs/heads/    one file per branch, content = commit hash

class BranchManager {
    std::string refsDir;
    std::string headFile;

public:
    explicit BranchManager(const std::string& root);

    void        setup();    // called once by init

    std::string current()                               const;
    std::string tip(const std::string& branch)         const;  // commit hash at branch head
    void        setTip(const std::string& branch,
                       const std::string& hash);

    bool        exists(const std::string& branch)      const;
    void        create(const std::string& branch);
    void        list()                                  const;
};
