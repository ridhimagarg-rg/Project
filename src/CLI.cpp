#include "CLI.h"
#include <iostream>
#include <stdexcept>
#include <string>

void CLI::usage() const {
    std::cout <<
        "usage: minigit <command> [args]\n"
        "\n"
        "  init               set up a new repo here\n"
        "  add   <file>       stage a file\n"
        "  commit <msg>       save a snapshot\n"
        "  log                show history\n"
        "  branch             list branches\n"
        "  branch <name>      create a branch\n"
        "\n";
}

int CLI::run(int argc, char* argv[]) {
    if (argc < 2) { usage(); return 1; }

    std::string cmd = argv[1];

    try {
        if (cmd == "init") {
            repo.cmdInit();

        } else if (cmd == "add") {
            if (argc < 3) throw std::runtime_error("add needs a filename");
            repo.cmdAdd(argv[2]);

        } else if (cmd == "commit") {
            if (argc < 3) throw std::runtime_error("commit needs a message");
            // glue remaining args together so you don't need quotes
            std::string msg;
            for (int i = 2; i < argc; i++) {
                if (i > 2) msg += " ";
                msg += argv[i];
            }
            repo.cmdCommit(msg);

        } else if (cmd == "log") {
            repo.cmdLog();

        } else if (cmd == "branch") {
            repo.cmdBranch(argc >= 3 ? argv[2] : "");

        } else {
            std::cerr << "unknown command: " << cmd << "\n";
            usage();
            return 1;
        }

    } catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
