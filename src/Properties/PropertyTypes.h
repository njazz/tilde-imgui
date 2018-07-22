// (c) 2017 Alex Nadzharov
// License: GPL3

#ifndef PROPERTY_TYPES
#define PROPERTY_TYPES

#include <vector>
#include <string>

struct StringEnum {
    std::vector<std::string> strings;
    int value = -1;
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
};

// ---

#endif // CM_PROPERTY_H
