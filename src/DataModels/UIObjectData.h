// (c) 2017 Alex Nadzharov
// License: GPL3

#ifndef UIOBJECTDATA_H
#define UIOBJECTDATA_H

#include <string>
#include "PropertyList.h"

typedef enum {
    os_FixedSize,
    os_FixedHeight,
    os_Free
} ObjectSizeMode;

////
/// \brief Data model for UIObject
class UIObjectData {

    std::string _dataString;
    PropertyList _properties;

    ObjectSizeMode _objectSizeMode;

public:
    //explicit UIObjectData();
    //~UIObjectData();

    std::string fullHelpName = "";

    bool errorBox = false;
    bool emptyBox = false;
    bool selected = false;

    int outletClicked = -1;
    int inletClicked = -1;

    std::string toString();
    PropertyList* properties();

    void setData(std::string inputData); ///> set both properties and Pd object string
    std::string data();

    void setObjectSizeConstraints(int minW, int minH); ///> sets all size constraints

    int minimumBoxWidth;
    int minimumBoxHeight;

    ObjectSizeMode objectSizeMode();
};


#endif // UIOBJECTDATA_H
