// (c) 2017 Alex Nadzharov
// License: GPL3

/*
#include "UIObjectData.h"

#include "Port.h"
#include "PropertyList.h"

#include "UIObjectData.h"

namespace tilde {
UIObjectData::UIObjectData(QObject* parent)
    : QObject(parent)
{
    // unused?
    _minimumBoxHeight = 20;
    _minimumBoxWidth = 20;

    //_pdObject = 0;
    _properties = new PropertyList();

    _errorBox = false;
}

UIObjectData::~UIObjectData()
{
    delete _properties;
}

void UIObjectData::setData(QString inputData) ///> set both properties and Pd object string
{

    //_dataString = inputData; //

    _dataString = _properties->extractFromPdFileString(inputData);

    _fullHelpName = _dataString.split(" ").at(0) + "-help.pd";
}

QString UIObjectData::data()
{
    return _dataString;
}

void UIObjectData::setObjectSize(t_objectSize sizeMode, int minW, int minH) ///> sets all size constraints
{
    _objectSizeMode = sizeMode;
    _minimumBoxWidth = minW;
    _minimumBoxHeight = minH;
}

QString UIObjectData::toQString() { return _dataString; }
PropertyList* UIObjectData::properties() { return _properties; }

QString UIObjectData::fullHelpName() { return _fullHelpName; }
bool UIObjectData::errorBox() { return _errorBox; }
void UIObjectData::setFullHelpName(QString fullHelpName) { _fullHelpName = fullHelpName; }
void UIObjectData::setErrorBox(bool errorBox) { _errorBox = errorBox; }

void UIObjectData::setMminimumBoxWidth(int w) { _minimumBoxWidth = w; };
void UIObjectData::setMminimumBoxHeight(int h) { _minimumBoxHeight = h; };

int UIObjectData::minimumBoxWidth() { return _minimumBoxWidth; }
int UIObjectData::minimumBoxHeight() { return _minimumBoxHeight; }
t_objectSize UIObjectData::objectSizeMode() { return _objectSizeMode; }
}

*/
