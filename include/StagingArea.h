#pragma once
#include <string>

// the staging area — tracks what will go into the next commit
//
// INDEX file format, one line per staged file:
//   filename|contenthash|objectpath

class StagingArea {
    std::string indexFile;
    std::string objDir;

public:
    explicit StagingArea(const std::string& root);

    void        stage(const std::string& filename);
    std::string snapshot()  const;   // returns raw index contents
    void        clear();
    bool        empty()     const;
};
