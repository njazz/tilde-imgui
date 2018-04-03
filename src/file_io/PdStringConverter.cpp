// (c) 2017 Alex Nadzharov
// License: GPL3

#include "PdStringConverter.h"
#include <vector>
#include <string>
#include <regex>


////
/// \brief unescapeString
/// \param input
/// \return
/// \deprecated needs cleanup - duplicate in PropertyList class
std::string PdStringConverter::unescapeString(std::string input)
{
    // todo regexp

    std::string ret = input;

    /*
    ret = input.split("\\ ").join(" ");
    ret = ret.split("\\n").join("\n");
    ret = ret.split("\\,").join(",");
    ret = ret.split("\\.").join(".");
    //ret = ret.split("\;").join(";");
    */

    return ret;
}

////
/// \brief escapeString
/// \param input
/// \return
/// \deprecated needs cleanup - duplicate in PropertyList class
std::string PdStringConverter::escapeString(std::string input)
{
    // todo regexp

    std::string ret = input;
    /*
    ret = input.split(" ").join("\\ ");
    ret = ret.split("\n").join("\\n");
    ret = ret.split(",").join("\\,");
    ret = ret.split(".").join("\\.");
    //ret = ret.split(";").join("\\;");
    */
    return ret;
}


std::vector<std::string> splitStringByToken(std::string& str, std::string token)
{
    std::vector<std::string> ret;

    std::regex rgx("\\s+");
    std::sregex_token_iterator iter(str.begin(),
        str.end(),
        rgx,
        -1);
    std::sregex_token_iterator end;
    for (; iter != end; ++iter)
        ret.push_back(*iter); //std::cout << *iter << '\n';

    return ret;
}

std::string joinStringWithToken(std::vector<std::string> vec, std::string token)
{
    std::string ret;
    auto& last = *(--vec.end());
    for (auto s : vec) {
        ret += s;
        if (&s != &last)
            ret += token;
    }
    return ret;
}
