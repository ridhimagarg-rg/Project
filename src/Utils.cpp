#include "Utils.h"

#include <fstream>
#include <sstream>
#include <ctime>
#include <filesystem>
#include <stdexcept>

namespace fs = std::filesystem;

std::string getTimestamp() {
    time_t now = time(nullptr);
    char buf[64];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return buf;
}

// FNV-1a — good enough for our purposes
std::string hashContent(const std::string& data) {
    uint64_t h = 14695981039346656037ULL;
    for (unsigned char c : data) {
        h ^= c;
        h *= 1099511628211ULL;
    }
    std::ostringstream oss;
    oss << std::hex << h;
    return oss.str();
}

std::string readFile(const std::string& path) {
    std::ifstream f(path, std::ios::binary);
    if (!f)
        throw std::runtime_error("can't open file: " + path);
    std::ostringstream ss;
    ss << f.rdbuf();
    return ss.str();
}

void writeFile(const std::string& path, const std::string& data) {
    fs::path p(path);
    if (p.has_parent_path())
        fs::create_directories(p.parent_path());

    std::ofstream f(path, std::ios::binary | std::ios::trunc);
    if (!f)
        throw std::runtime_error("can't write file: " + path);
    f << data;
}

bool pathExists(const std::string& path) {
    return fs::exists(path);
}