// (c) 2017 Alex Nadzharov
// License: GPL3

#ifndef PROPERTY_TYPES
#define PROPERTY_TYPES

#include <string>
#include <vector>

#include <initializer_list>
#include <tuple>

struct StringEnum {
    std::vector<std::string> strings = {};
    int value = -1;

    bool operator==(StringEnum& s)
    {
        return (value == s.value) && (strings == s.strings);
    }

    bool operator==(const StringEnum& s)
    {
        return (value == s.value) && (strings == s.strings);
    }

    StringEnum(std::vector<std::string> s = {}, int v = -1)
    {
        strings = s;
        value = v;
    }
};

class Color {
    float _v[4];

public:
    Color(float r = 0, float g = 0, float b = 0, float a = 1.)
    {
        _v[0] = r;
        _v[1] = g;
        _v[2] = b;
        _v[3] = a;
    }

    float* v() { return _v; }

    bool operator==(Color& c)
    {
        return (c.v()[0] == _v[0]) && (c.v()[1] == _v[1]) && (c.v()[2] == _v[2]) && (c.v()[3] == _v[3]);
    }

    bool operator==(const Color& c)
    {
        return (c._v[0] == _v[0]) && (c._v[1] == _v[1]) && (c._v[2] == _v[2]) && (c._v[3] == _v[3]);
    }
};

// ---

#endif // CM_PROPERTY_H
