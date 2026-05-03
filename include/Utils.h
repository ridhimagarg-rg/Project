#pragma once
#include <string>

// just some helpers used across the whole project

std::string getTimestamp();
std::string hashContent(const std::string& data);
std::string readFile(const std::string& path);
void        writeFile(const std::string& path, const std::string& data);
bool        pathExists(const std::string& path);