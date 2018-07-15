// (c) 2017 Alex Nadzharov
// License: GPL3

#include "PdStringConverter.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
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


std::vector<std::string> splitStringByToken(std::string str, std::string delimiter)
{
//    std::vector<std::string> ret;

//    std::regex rgx("\\s+");
//    std::sregex_token_iterator iter(str.begin(),
//        str.end(),
//        rgx,
//        -1);
//    std::sregex_token_iterator end;
//    for (; iter != end; ++iter)
//        ret.push_back(*iter); //std::cout << *iter << '\n';

//    return ret;

//    std::stringstream ss(str);
//    std::string item;
//    std::vector<std::string> tokens;
//    while (ss.getline(item, token)) {
//        tokens.push_back(item);
//    }
//    return tokens;


    std::vector<std::string> tokens;
    size_t pos = 0;
    while (( pos = str.find(delimiter)) != std::string::npos) {
        tokens.push_back( str.substr(0, pos) );
        str.erase(0, pos + delimiter.length());
    }
    tokens.push_back(str);
    return tokens;
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
