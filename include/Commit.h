#pragma once
#include <string>

class Commit {
public:
    std::string hash;
    std::string parent;   // empty string means this is the first commit
    std::string message;
    std::string when;
    std::string branch;
    std::string tree;     // raw index snapshot at the time of commit

    Commit() = default;

    std::string         serialize()                        const;
    static Commit       deserialize(const std::string& s);
};
