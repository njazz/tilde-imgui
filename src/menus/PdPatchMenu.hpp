//

#include "IUMainMenuBase.hpp"
#include "PdCommonMenus.hpp"

#include "IUPopupMenu.hpp"

#pragma once

class PdPatchEditMenu : public IUMenuBase {
public:
    virtual void _shortcutContents() override;
    virtual void _drawContents() override;

    bool* editModeFlag = 0;

    static const int aEditMode = 1;

    static const int aUndo = 5;
    static const int aRedo = 6;

    static const int aCut = 10;
    static const int aCopy = 11;
    static const int aPaste = 12;

    static const int aSelectAll = 15;

    static const int aDelete = 20;

    std::string undoActionName = "";
    std::string redoActionName = "";
};

class PdPatchPutMenu : public IUMenuBase {
public:
    virtual void _shortcutContents() override;
    virtual void _drawContents() override;

    static const int aFileNew = 1;

    static const int aObject = 10;
    static const int aMessage = 11;
    static const int aComment = 12;

    static const int aBang = 20;
    static const int aToggle = 21;
    static const int aNumber = 22;

    static const int aSlider = 30;
    static const int aRadioButtons = 40;
    static const int aArray = 50;

};

class PdPatchArrangeMenu : public IUMenuBase {
public:
    bool *showGrid = 0;
    bool *snapToGrid = 0;

    virtual void _shortcutContents() override;
    virtual void _drawContents() override;


    static const int aAlignLeft = 50;
    static const int aAlignCenter = 51;
    static const int aAlignRight = 52;
    static const int aAlignTop = 53;
    static const int aAlignBottom = 54;
    static const int aDistributeH = 55;
    static const int aDistributeV = 56;

    static const int aZoomIn = 70;
    static const int aZoomOut = 71;
    static const int aZoomOne = 72;
};

class PdPatchMenu : public IUMainMenuBase {

public:
    PdCommonMenus* common = 0;
    //    PdCommonFileMenu menuFile;

    PdPatchEditMenu menuEdit;
    PdPatchPutMenu menuPut;
    PdPatchArrangeMenu menuArrange;

    //    PdCommonWindowMenu menuWindow;
    //    PdCommonMediaMenu menuMedia;
    //    PdCommonHelpMenu menuHelp;

    PdPatchMenu(PdCommonMenus* m);
};

class PdObjectMenu:public IUPopupMenu {

public:
    bool propertiesWindow = false;

    virtual void _drawContents() override;

    static const int aProperties = 10;
    static const int aHelp = 11;
};
