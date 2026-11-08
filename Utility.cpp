#include "Utility.h"

std::string Utility::trim(const std::string &string)
{
    std::size_t firstIndex = string.find_first_not_of(" \t");
    std::size_t secondIndex = string.find_last_not_of(" \t");

    if (firstIndex == std::string::npos || secondIndex == std::string::npos)
        return "";

    return string.substr(firstIndex, secondIndex - firstIndex + 1);
}

std::vector<std::string> Utility::split(const std::string& string, char delimiter) {
    std::vector<std::string> result;
    std::string token = "";
    bool inQuotes = false;

    for (char c : string) {

        if (c == '\"') {
            inQuotes = !inQuotes;
            token.push_back(c);
        } else if (c == delimiter && !inQuotes) {
            result.push_back(token);
            token.clear();
        } else {
            token.push_back(c);
        }
    }

    if (!token.empty())
        result.push_back(token);

    return result;
}

std::string Utility::toLower(const std::string &string)
{
    std::string result = string;
    
    for (std::size_t i = 0; i < result.size(); i++)
        result[i] = static_cast<char>(std::tolower(result[i]));

    return result;
}

std::string Utility::removeEscapeCharacters(const std::string &string)
{
    std::string result;
    bool inQuotes = false;
    bool escapeNext = false;

    for (char c : string) {

        if (escapeNext) {
            if (c == '\\' || c == '\"')
                result.push_back(c);  
            escapeNext = false; 
        } else if (c == '\\') {
            escapeNext = true;  
        } else if (c == '\"') {
            if (inQuotes) {
                break;
            } else {
                inQuotes = true; 
                continue;  
            }
        } else {
            if (inQuotes)
                result.push_back(c);
        }
    }

    return result;
}

std::size_t Utility::countCommas(const std::string& input) {
    std::size_t commaCount = 0;
    for (char c : input) {
        if (c == ',') {
            commaCount++;
        }
    }
    return commaCount;
}