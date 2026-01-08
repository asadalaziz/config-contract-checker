#include "../include/JsonPrinter.h"
#include <iostream>

void JsonPrinter::print(const std::vector<Violation>& violations) {
    std::cout << "{\n";
    std::cout << "  \"violations\": [\n";

    for (size_t i = 0; i < violations.size(); ++i) {
        std::cout << "    {\n";
        std::cout << "      \"message\": \""
                  << violations[i].message << "\"\n";
        std::cout << "    }";

        if (i != violations.size() - 1)
            std::cout << ",";

        std::cout << "\n";
    }

    std::cout << "  ]\n";
    std::cout << "}\n";
}
