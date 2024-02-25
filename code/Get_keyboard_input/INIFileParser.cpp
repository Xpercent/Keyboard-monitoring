#include "INIFileParser.h"
#include <fstream>
#include <sstream>

INIFileParser::INIFileParser(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        // Handle error: Unable to open file
        return;
    }

    std::string currentSection;
    std::string line;

    while (std::getline(file, line)) {
        // Trim leading and trailing whitespaces
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);

        // Skip empty lines and comments
        if (line.empty() || line[0] == ';') {
            continue;
        }

        if (line[0] == '[' && line[line.size() - 1] == ']') {
            // New section
            currentSection = line.substr(1, line.size() - 2);
        } else {
            // Key-value pair in current section
            std::size_t equalPos = line.find('=');
            if (equalPos != std::string::npos) {
                std::string key = line.substr(0, equalPos);
                std::string value = line.substr(equalPos + 1);
                iniData[currentSection][key] = value;
            }
        }
    }

    file.close();
}

INIFileParser::~INIFileParser() {
    // Destructor, if needed
}

std::string INIFileParser::getValue(const std::string& section, const std::string& key) const {
    auto sectionIt = iniData.find(section);
    if (sectionIt != iniData.end()) {
        auto keyIt = sectionIt->second.find(key);
        if (keyIt != sectionIt->second.end()) {
            return keyIt->second;
        }
    }

    // Handle error: Section or key not found
    return "";
}
