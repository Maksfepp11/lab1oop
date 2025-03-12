#include <windows.h>
#include "price.hpp"

int main() {
    SetConsoleOutputCP(65001); // Встановлює кодування UTF-8
    processFile(); // Викликає функцію обробки цін
    return 0;
}
