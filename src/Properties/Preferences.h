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
    Preferences():PropertyList()
    {
        create("Version","System","0",std::string(APP_VERSION));
        create("Search Paths", "PureData","0", std::vector<std::string> ({"~/"}));

        get("Version")->readOnly = true;
    }

    void loadFromJSONFile(){};
    void saveToJSONFile(){};

};

#endif // CM_PREFERENCES_H
