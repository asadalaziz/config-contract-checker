#ifndef RULE_H
#define RULE_H

#include <string>

enum class Operator {
    EQUAL,
    LESS,
    GREATER,
    LESS_EQUAL,
    GREATER_EQUAL
};

struct Rule {
    std::string ifKey;
    std::string ifValue;

    std::string thenKey;
    Operator op;
    std::string thenValue;
};

#endif
