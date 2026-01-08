#ifndef RULE_ENGINE_H
#define RULE_ENGINE_H

#include <vector>
#include <unordered_map>
#include <string>
#include "Rule.h"
#include "Violation.h"

class RuleEngine {
public:
    std::vector<Violation> evaluate(
        const std::unordered_map<std::string, std::string>& config,
        const std::vector<Rule>& rules
    );
};

#endif
