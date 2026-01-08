#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include <unordered_map>
#include <string>

class ConfigParser {
public:
    bool load(const std::string& filePath);
    const std::unordered_map<std::string, std::string>& getConfig() const;

private:
    std::unordered_map<std::string, std::string> config;
};

#endif
