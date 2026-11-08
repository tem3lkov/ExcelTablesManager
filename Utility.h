#pragma once
#include <string>
#include <vector>

class Utility
{
public:
    static std::string trim(const std::string& string);
    static std::vector<std::string> split(const std::string& string, char delimiter);
    static std::string toLower(const std::string& string);
    static std::string removeEscapeCharacters(const std::string& string);
    static std::size_t countCommas(const std::string& input);
};