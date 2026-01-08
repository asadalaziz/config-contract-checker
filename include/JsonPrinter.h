#ifndef JSON_PRINTER_H
#define JSON_PRINTER_H

#include <vector>
#include "Violation.h"

class JsonPrinter {
public:
    static void print(const std::vector<Violation>& violations);
};

#endif
