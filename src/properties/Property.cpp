// (c) 2017 Alex Nadzharov
// License: GPL3

#include "Property.h"

template <>
std::string PropertyT<float>::asPdString()
{
    return std::to_string(*_data);
};

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

template <>
std::string PropertyT<int*>::asPdString()
{
    return std::to_string(**_data);
};

template <>
std::string PropertyT<std::string>::asPdString()
{
    return *_data;
};

template <>
std::string PropertyT<std::string*>::asPdString()
{
    return **_data;
};
