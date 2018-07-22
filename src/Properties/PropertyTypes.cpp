// (c) 2017 Alex Nadzharov
// License: GPL3

#include "PropertyTypes.h"
#include "json.hpp"
#include "Property.h"

#include <string>

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
    if (!j.size() == 4)
        return;

    for (int i = 0; i < 4; i++)
        _data->v()[i] = j[i];
};

//

template <>
void PropertyT<Color>::fromPdString(std::string str)
{
//    auto v = splitStringByToken(str, " ");
//    int s = (_data->size()<v.size()) ? _data->size() : v.size();

    ///> \todo Color - fromPdString
}

template <>
std::string PropertyT<Color>::asPdString()
{
    std::string ret;
//    for (auto it = _data->begin(); it != _data->end(); ++it) {
//        ret += std::to_string(**it);
//        if (it != (_data->end() - 1))
//            ret += " ";
//    }

    ///> \todo Color - asPdString
    return ret;
}
