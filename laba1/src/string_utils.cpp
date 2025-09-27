#include "../include/string_utils.h"
#include <string>
#include <cctype>

std::string extractNumbers(const std::string& input) {
    std::string result;
    
    for (char c : input) {
        if (std::isdigit(c)) {
            result += c;
        }
    }
    
    return result;
}
