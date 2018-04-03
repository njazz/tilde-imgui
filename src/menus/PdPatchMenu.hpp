//

#include "IUMainMenuBase.hpp"
#include "PdCommonMenus.hpp"

class PdPatchEditMenu : public IUMenuBase {
public:
    virtual void shortcuts() override;
    virtual void draw() override;

    bool* editModeFlag = 0;

    static const int aEditMode = 1;

    static const int aCut = 10;
    static const int aCopy = 11;
    static const int aPaste = 12;
};

class PdPatchPutMenu : public IUMenuBase {
public:
    virtual void shortcuts() override;
    virtual void draw() override;

    static const int aFileNew = 1;
};

class PdPatchArrangeMenu : public IUMenuBase {
public:
    ;
    virtual void shortcuts() override;
    virtual void draw() override;

    static const int aAlignLeft = 50;
    static const int aAlignCenter = 51;
    static const int aAlignRight = 52;
    static const int aAlignTop = 53;
    static const int aAlignBottom = 54;
    static const int aDistributeH = 55;
    static const int aDistributeV = 56;
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
