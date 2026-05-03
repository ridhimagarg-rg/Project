#include "StagingArea.h"
#include "Utils.h"

#include <sstream>
#include <iostream>
#include <stdexcept>

StagingArea::StagingArea(const std::string& root)
    : indexFile(root + "/.minigit/INDEX"),
      objDir   (root + "/.minigit/objects/") {}

void StagingArea::stage(const std::string& filename) {
    if (!pathExists(filename))
        throw std::runtime_error("file not found: " + filename);

    auto content = readFile(filename);
    auto hash    = hashContent(content);
    auto objPath = objDir + hash;

    // save blob
    writeFile(objPath, content);

    // rewrite index — replace existing entry if file was already staged
    auto existing = pathExists(indexFile) ? readFile(indexFile) : "";
    std::istringstream ss(existing);
    std::string line, newIndex;
    bool updated = false;

    while (std::getline(ss, line)) {
        if (line.empty()) continue;
        auto fname = line.substr(0, line.find('|'));
        if (fname == filename) {
            newIndex += filename + "|" + hash + "|" + objPath + "\n";
            updated = true;
        } else {
            newIndex += line + "\n";
        }
    }

    if (!updated)
        newIndex += filename + "|" + hash + "|" + objPath + "\n";

    writeFile(indexFile, newIndex);
    std::cout << "staged: " << filename << "\n";
}

std::string StagingArea::snapshot() const {
    return pathExists(indexFile) ? readFile(indexFile) : "";
}

void StagingArea::clear() {
    writeFile(indexFile, "");
}

bool StagingArea::empty() const {
    for (char c : snapshot())
        if (!std::isspace((unsigned char)c)) return false;
    return true;
}
