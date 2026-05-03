#include "Logger.h"

#include <iostream>
#include <sstream>

Logger::Logger(const CommitStore& cs, const BranchManager& b)
    : store(cs), bm(b) {}

void Logger::show() const {
    auto branch = bm.current();
    auto hash   = bm.tip(branch);

    if (hash.empty()) {
        std::cout << "no commits yet on '" << branch << "'\n";
        return;
    }

    std::cout << "branch: " << branch << "\n\n";

    while (!hash.empty() && store.has(hash)) {
        auto c = store.load(hash);

        std::cout << "commit  " << c.hash   << "\n"
                  << "date    " << c.when    << "\n"
                  << "        " << c.message << "\n\n";

        // print the files that were in this commit
        std::istringstream ss(c.tree);
        std::string line;
        while (std::getline(ss, line)) {
            if (line.empty()) continue;
            auto end = line.find('|');
            std::cout << "   " << line.substr(0, end) << "\n";
        }

        std::cout << "\n" << std::string(50, '-') << "\n\n";
        hash = c.parent;
    }
}
