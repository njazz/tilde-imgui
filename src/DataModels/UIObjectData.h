// (c) 2017 Alex Nadzharov
// License: GPL3

#ifndef UIOBJECTDATA_H
#define UIOBJECTDATA_H

#include <string>
#include "PropertyList.h"

#include "pd_object.h"

typedef enum {
    os_FixedSize,
    os_FixedHeight,
    os_Free
} ObjectSizeMode;

////
/// \brief Data model for UIObject
class UIObjectData {

    std::string _dataString = "";
    PropertyList _properties;

    ObjectSizeMode _objectSizeMode = os_FixedHeight;

public:
    explicit UIObjectData(){};
    //~UIObjectData();

    xpd::ObjectId pdObjectID = 0;
    xpd::PdObject* pdObject = 0;

    std::string fullHelpName = "";

    bool errorBox = false;
    bool emptyBox = false;
    bool selected = false;
    bool isCanvas = false;
    bool isAbstraction = false;

    int outletClicked = -1;
    int inletClicked = -1;

    int inletCount = 0;
    int outletCount = 0;


    PropertyList* properties() {return &_properties;};

    void setData(std::string inputData); ///< set both properties and Pd object string
    std::string& data();

    void setObjectSizeConstraints(int minW, int minH); ///< sets all size constraints

    int minimumBoxWidth = 20;
    int minimumBoxHeight = 10;

    ObjectSizeMode objectSizeMode();

    void syncFromServerObject();
    void syncToServerObject();
};


#endif // UIOBJECTDATA_H
