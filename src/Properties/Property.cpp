// (c) 2017 Alex Nadzharov
// License: GPL3

#include "Property.h"

#include "json.hpp"

#include "PdStringConverter.h"
json PropertyBase::toJSON()
{
    json j;

    j["read_only"] = readOnly;
    j["group"] = group;
    j["version"] = version;
    j["data"] = dataToJSON();

    return j;
}
void PropertyBase::fromJSON(json j)
{
    try {
        readOnly = j["read_only"];
        group = j["group"];
        version = j["version"];
        dataFromJSON(j["data"]);
    } catch (std::exception& e) {
        printf("error parsing JSON: %s", e.what());
    }
}
std::string PropertyBase::toJSONString()
{
    return toJSON().dump();
}

void PropertyBase::fromJSONString(std::string s)
{
    try {
        json j = json::parse(s);
        if (j.is_object())
            fromJSON(j);
    } catch (std::exception& e) {
        printf("ERROR: bad JSON string (%s)\n", e.what());
    }
}

json PropertyBase::dataToJSON()
{
    json j = "";
    return j;
};
void PropertyBase::dataFromJSON(json j) {}

PropertyBase* createFromJSON(json j)
{
    // TODO:

    return 0;

//    auto ret = new PropertyT<decltype(j.value())>();
//    ret->fromJSON(j);
//    return ret;
}

// ---

template <>
void PropertyT<float>::fromPdString(std::string str)
{
    *_data = std::stof(str);
}

template <>
std::string PropertyT<float>::asPdString()
{
    return std::to_string(*_data);
};

template <>
void PropertyT<float*>::fromPdString(std::string str)
{
    **_data = std::stof(str);
}

template <>
std::string PropertyT<float*>::asPdString()
{
    return std::to_string(**_data);
};

template <>
std::string PropertyT<int>::asPdString()
{
    return std::to_string(*_data);
};

template<>
void PropertyT<int>::fromPdString(std::string str)
{
    *_data = std::stoi(str);
}

template <>
std::string PropertyT<int*>::asPdString()
{
    return std::to_string(**_data);
};

template <>
void PropertyT<std::string>::fromPdString(std::string str)
{
    *_data = str;
}

template <>
std::string PropertyT<std::string>::asPdString()
{
    return *_data;
};

template <>
void PropertyT<std::string*>::fromPdString(std::string str)
{
   **_data = str;
}

template <>
std::string PropertyT<std::string*>::asPdString()
{
    return **_data;
};

//

template <>
void PropertyT<bool>::fromPdString(std::string str)
{
    *_data = std::stoi(str);
}

template <>
std::string PropertyT<bool>::asPdString()
{
    return std::to_string((int)*_data);
};

template <>
std::string PropertyT<std::vector<std::string>>::asPdString()
{
    std::string ret;
//    return std::to_string((int)*_data);
    for (int i=0;i<(_data->size()-1);i++)
        ret += (*_data)[i] +" ";
    if (_data->size())
        ret += (*_data)[_data->size()-1];
    return ret;
};

template <>
void PropertyT<std::vector<std::string>>::fromPdString(std::string str)
{
   *_data = splitStringByToken(str," ");
}

// ---
template <>
json PropertyT<int>::dataToJSON()
{
    json j;
    j = *_data;
    return j;
};

template <>
void PropertyT<int>::dataFromJSON(json j)
{
    if (j.is_number())
        *_data = j;
};

template <>
json PropertyT<int*>::dataToJSON()
{
    json j;
    j = **_data;
    return j;
};

template <>
void PropertyT<int*>::dataFromJSON(json j)
{
    if (j.is_number())
        **_data = j;
};

template <>
json PropertyT<float>::dataToJSON()
{
    json j;
    j = *_data;
    return j;
};

template <>
void PropertyT<float>::dataFromJSON(json j)
{
    if (j.is_number())
        *_data = j;
};

template <>
json PropertyT<float*>::dataToJSON()
{
    json j;
    j = **_data;
    return j;
};

template <>
void PropertyT<float*>::dataFromJSON(json j)
{
    if (j.is_number())
        **_data = j;
};

template <>
json PropertyT<bool>::dataToJSON()
{
    json j;
    j = *_data;
    return j;
};

template <>
void PropertyT<bool>::dataFromJSON(json j)
{
    if (j.is_boolean())
        *_data = j;
};

template <>
json PropertyT<bool*>::dataToJSON()
{
    json j;
    j = **_data;
    return j;
};

template <>
void PropertyT<bool*>::dataFromJSON(json j)
{
    if (j.is_boolean())
        **_data = j;
};

template <>
json PropertyT<std::vector<float*> >::dataToJSON()
{
    json j;
    // todo
    return j;
};

template <>
void PropertyT<std::vector<float*> >::fromPdString(std::string str)
{
    auto v = splitStringByToken(str, " ");

    // TODO!
    assert(0);
}

template <>
std::string PropertyT<std::vector<float*> >::asPdString()
{
    // todo
    return "";
}

template <>
void PropertyT<std::vector<float*> >::dataFromJSON(json j){
    //    if (j.is_array())
    // todo
};

template <>
json PropertyT<std::string>::dataToJSON()
{
    json j;
    j = *_data;
    return j;
};

template <>
void PropertyT<std::string>::dataFromJSON(json j)
{
    if (j.is_string())
        *_data = j;
};

template <>
json PropertyT<std::string*>::dataToJSON()
{
    json j;
    j = **_data;
    return j;
};

template <>
void PropertyT<std::string*>::dataFromJSON(json j)
{
    if (j.is_string())
        **_data = j;
};


template <>
json PropertyT<std::vector<std::string> >::dataToJSON()
{
    json j;
    j = *_data;
    return j;
};

template <>
void PropertyT<std::vector<std::string> >::dataFromJSON(json j)
{
    if (j.is_array())
    {
        (_data)->clear();
        for (auto s: j)
            (_data)->push_back(s);
    }

};

// TODO:
//template <>
//json PropertyT<char const*>::dataToJSON()
//{
//    json j;
//    j = **_data;
//    return j;
//};

//template <>
//void PropertyT<char const*>::dataFromJSON(json j)
//{
//    if (j.is_string())
//        **_data = j;
//};
