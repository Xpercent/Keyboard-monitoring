#ifndef INI_FILE_PARSER_H
#define INI_FILE_PARSER_H

#include <string>
#include <unordered_map>

class INIFileParser {
public:
    INIFileParser(const std::string& filename);
    ~INIFileParser();

    std::string getValue(const std::string& section, const std::string& key) const;

private:
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> iniData;
};

#endif  // INI_FILE_PARSER_H
