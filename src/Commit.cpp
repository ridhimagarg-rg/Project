#include "Commit.h"
#include <sstream>

// format is dead simple — key:value lines, tree content sandwiched
// between tree_begin / tree_end markers

std::string Commit::serialize() const {
    std::ostringstream out;
    out << "hash:"    << hash    << "\n"
        << "parent:"  << parent  << "\n"
        << "message:" << message << "\n"
        << "when:"    << when    << "\n"
        << "branch:"  << branch  << "\n"
        << "tree_begin\n"
        << tree
        << "tree_end\n";
    return out.str();
}

Commit Commit::deserialize(const std::string& s) {
    Commit c;
    std::istringstream ss(s);
    std::string line;
    bool inTree = false;

    while (std::getline(ss, line)) {
        if (line == "tree_begin") { inTree = true;  continue; }
        if (line == "tree_end")   { inTree = false; continue; }

        if (inTree) {
            c.tree += line + "\n";
            continue;
        }

        auto sep = line.find(':');
        if (sep == std::string::npos) continue;

        auto key = line.substr(0, sep);
        auto val = line.substr(sep + 1);

        if      (key == "hash")    c.hash    = val;
        else if (key == "parent")  c.parent  = val;
        else if (key == "message") c.message = val;
        else if (key == "when")    c.when    = val;
        else if (key == "branch")  c.branch  = val;
    }

    return c;
}
