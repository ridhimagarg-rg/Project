#pragma once
#include "Repository.h"

class CLI {
    Repository repo;
    void usage() const;

public:
    int run(int argc, char* argv[]);
};
