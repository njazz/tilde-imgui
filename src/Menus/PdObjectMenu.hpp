#include "IUMainMenuBase.hpp"
#include "PdCommonMenus.hpp"

#include "IUPopupMenu.hpp"

#pragma once

class PdObjectMenu:public IUPopupMenu {

public:
    bool propertiesWindow = false;
    bool canvas = false;

    virtual void _drawContents() override;

    static const int aProperties = 10;
    static const int aHelp = 11;

    static const int aOpenWindow = 21;
    static const int aOpenSubwindow = 22;
    static const int aOpenTab = 23;

};
