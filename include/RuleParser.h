#ifndef RULE_PARSER_H
#define RULE_PARSER_H

#include <vector>
#include <string>
#include "Rule.h"

class RuleParser {
public:
    bool load(const std::string& filePath);
    const std::vector<Rule>& getRules() const;

private:
    std::vector<Rule> rules;
};

#endif
