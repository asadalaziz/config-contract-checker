#include "../include/RuleEngine.h"

std::vector<Violation> RuleEngine::evaluate(
    const std::unordered_map<std::string, std::string>& config,
    const std::vector<Rule>& rules
) {
    std::vector<Violation> violations;

    for (const auto& rule : rules) {

        // Step 1: Check IF condition
        auto ifIt = config.find(rule.ifKey);
        if (ifIt == config.end())
            continue;

        if (ifIt->second != rule.ifValue)
            continue;

        // Step 2: IF is true, enforce THEN
        auto thenIt = config.find(rule.thenKey);
        if (thenIt == config.end())
            continue;

        bool violation = false;

        std::string actualValue = thenIt->second;
        std::string expectedValue = rule.thenValue;

        if (rule.op == Operator::EQUAL) {
            violation = (actualValue != expectedValue);
        }
        else {
        // Numeric comparison
            int actual = std::stoi(actualValue);
            int expected = std::stoi(expectedValue);

            if (rule.op == Operator::LESS)
                violation = !(actual < expected);
            else if (rule.op == Operator::LESS_EQUAL)
                violation = !(actual <= expected);
            else if (rule.op == Operator::GREATER)
                violation = !(actual > expected);
            else if (rule.op == Operator::GREATER_EQUAL)
                violation = !(actual >= expected);
        }


        // Step 3: Record violation
        if (violation) {
            Violation v;
            v.message =
                "Rule violated: IF " + rule.ifKey + "=" + rule.ifValue +
                " THEN " + rule.thenKey + "=" + rule.thenValue +
                " (found " + thenIt->second + ")";
            violations.push_back(v);
        }
    }

    return violations;
}
