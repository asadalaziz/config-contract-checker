#include "../include/RuleParser.h"
#include <fstream>
#include <iostream>
#include <sstream>

bool RuleParser::load(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cout << "Failed to open contract file\n";
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Example: IF mode=production THEN debug=false
        Rule rule;

        size_t ifPos = line.find("IF ");
        size_t thenPos = line.find(" THEN ");

        if (ifPos == std::string::npos || thenPos == std::string::npos)
            continue;

        std::string ifPart = line.substr(3, thenPos - 3);
        std::string thenPart = line.substr(thenPos + 6);

        size_t eqPos = ifPart.find('=');
        rule.ifKey = ifPart.substr(0, eqPos);
        rule.ifValue = ifPart.substr(eqPos + 1);

        // Detect operator in THEN part
        if (thenPart.find("<=") != std::string::npos) {
            rule.op = Operator::LESS_EQUAL;
            size_t pos = thenPart.find("<=");
            rule.thenKey = thenPart.substr(0, pos);
            rule.thenValue = thenPart.substr(pos + 2);
        }
        else if (thenPart.find(">=") != std::string::npos) {
            rule.op = Operator::GREATER_EQUAL;
            size_t pos = thenPart.find(">=");
            rule.thenKey = thenPart.substr(0, pos);
            rule.thenValue = thenPart.substr(pos + 2);
        }
        else if (thenPart.find("<") != std::string::npos) {
            rule.op = Operator::LESS;
            size_t pos = thenPart.find("<");
            rule.thenKey = thenPart.substr(0, pos);
            rule.thenValue = thenPart.substr(pos + 1);
        }
        else if (thenPart.find(">") != std::string::npos) {
            rule.op = Operator::GREATER;
            size_t pos = thenPart.find(">");
            rule.thenKey = thenPart.substr(0, pos);
            rule.thenValue = thenPart.substr(pos + 1);
        }
        else if (thenPart.find("=") != std::string::npos) {
            rule.op = Operator::EQUAL;
            size_t pos = thenPart.find("=");
            rule.thenKey = thenPart.substr(0, pos);
            rule.thenValue = thenPart.substr(pos + 1);
        }


        rules.push_back(rule);
    }

    file.close();
    return true;
}

const std::vector<Rule>& RuleParser::getRules() const {
    return rules;
}
