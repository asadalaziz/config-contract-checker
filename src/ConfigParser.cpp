#include "../include/ConfigParser.h"
#include <fstream>
#include <iostream>

bool ConfigParser::load(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cout << "Failed to open config file\n";
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        size_t pos = line.find('=');
        if (pos != std::string::npos) {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);
            config[key] = value;
        }
    }

    file.close();
    return true;
}

const std::unordered_map<std::string, std::string>& ConfigParser::getConfig() const {
    return config;
}
