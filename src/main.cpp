#include <iostream>
#include "../include/ConfigParser.h"
#include "../include/RuleParser.h"
#include "../include/RuleEngine.h"
#include "../include/JsonPrinter.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Usage: checker <config_file> <contract_file>\n";
        return 1;
    }

    ConfigParser configParser;
    RuleParser ruleParser;
    RuleEngine engine;

    if (!configParser.load(argv[1])) return 1;
    if (!ruleParser.load(argv[2])) return 1;

    auto violations = engine.evaluate(
        configParser.getConfig(),
        ruleParser.getRules()
    );

    JsonPrinter::print(violations);
    return 0;
}
