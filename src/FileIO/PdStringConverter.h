#ifndef FILEPARSERCONVERTER_H
#define FILEPARSERCONVERTER_H

#include <string>

////
/// \brief Escape/unescape functions for FileParser. moved here for easier testing
class PdStringConverter {
public:
    static std::string unescapeString(std::string input); ///> parse string from file
    static std::string escapeString(std::string input); ///> parse string to file
};

std::vector<std::string> splitStringByToken(std::string& str, std::string token);
std::string joinStringWithToken(std::vector<std::string> vec, std::string token);

#endif // FILEPARSERCONVERTER_H
