// (c) 2017 Alex Nadzharov
// License: GPL3

#ifndef CM_PREFERENCES_H
#define CM_PREFERENCES_H

#include "PropertyList.h"
#include "json.hpp"


// move
#define APP_VERSION "0.01ß"

class Preferences : public PropertyList
{
public:
    Preferences();

    void loadFromJSONFile(){};
    void saveToJSONFile(){};

};

#endif // CM_PREFERENCES_H
