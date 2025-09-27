#include <iostream>
#include <string>
#include "../include/string_utils.h"

int main() {
    std::string input;
    
    std::cout << "Введите строку: ";
    std::getline(std::cin, input);
    
    std::string numbers = extractNumbers(input);
    
    std::cout << "Извлеченные цифры: " << numbers << std::endl;
    
    return 0;
}
