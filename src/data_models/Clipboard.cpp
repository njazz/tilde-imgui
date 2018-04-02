// (c) 2017 Alex Nadzharov
// License: GPL3

#include "Clipboard.h"

#include <iostream>

void Clipboard::append(std::vector<std::string> data)
{
    //    _data += data;
}

void Clipboard::clear()
{
    _data.clear();
}

size_t Clipboard::size()
{
    return _data.size();
}

std::vector<std::string> Clipboard::data()
{
    return _data;
}

void Clipboard::setStringAt(int idx, std::string str)
{
    if (idx < _data.size())
        _data[idx] = str;
    else
        std::cout << "clipboard: out of range\n";
}

std::string Clipboard::get(int idx)
{
    std::string ret ;

    if (idx < _data.size())
        return std::string(_data[idx]);
    else
        std::cout << "clipboard: out of range\n";

    return ret;
}

