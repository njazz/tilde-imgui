// (c) 2017 Alex Nadzharov
// License: GPL3

#include "PropertyTypes.h"
#include "Property.h"
#include "json.hpp"

#include <string>

#include "PdStringConverter.h"

#include <algorithm>

#include <tuple>
#include <initializer_list>

template <>
json PropertyT<StringEnum>::dataToJSON()
{
    json j = json::object();
    j["strings"] = _data->strings;
    j["index"] = _data->value;
    return j;
};

template <>
void PropertyT<StringEnum>::dataFromJSON(json j)
{
    if (!j.is_object()) return;
    if (!j["strings"].is_array()) return;
    if (!j["index"].is_number()) return;

    for (int i=0;i<j["strings"].size();i++)
        _data->strings.push_back(j["strings"].at(i));
    _data->value = j["index"];
};

template <>
void PropertyT<StringEnum>::fromPdString(std::string str)
{
    auto v = splitStringByToken(str, " ");

    if (v.size()<2) return;
    _data->value = std::stoi(v[0]);

    v.erase(v.begin());

    ///\todo catch exception
    /// \todo escape strings
    _data->strings = v;
}

template <>
std::string PropertyT<StringEnum>::asPdString()
{
    std::string ret;

    /// \todo unescape strings

    ret = std::to_string(_data->value) + " ";
    ret += joinStringWithToken(_data->strings," ");
    ret = ret.substr(0,ret.size()-1);

    return ret;
}

// ---

template <>
json PropertyT<Color>::dataToJSON()
{
    json j = json::array();
    for (int i = 0; i < 4; i++)
        j.push_back(_data->v()[i]);
    return j;
};

template <>
void PropertyT<Color>::dataFromJSON(json j)
{
    if (!j.is_array())
        return;
    if (!(j.size() == 4))
        return;

    for (int i = 0; i < 4; i++)
        _data->v()[i] = j[i];
};

template <>
void PropertyT<Color>::fromPdString(std::string str)
{
    auto v = splitStringByToken(str, " ");
    if (v.size() != 4)
        return;

    ///\todo catch exception
    for (int i = 0; i < 4; i++)
        _data->v()[i] = std::stof(v[i]);
}

template <>
std::string PropertyT<Color>::asPdString()
{
    std::string ret;

    for (int i = 0; i < 3; i++)
        ret += std::to_string(_data->v()[i]) + " ";
    ret += std::to_string(_data->v()[3]);

    return ret;
}
