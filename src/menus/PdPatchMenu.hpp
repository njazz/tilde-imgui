//

#include "IUMainMenuBase.hpp"
#include "PdCommonMenus.hpp"

class PdPatchEditMenu : public IUMenuBase {
public:
    virtual void draw() override;

    bool* editModeFlag = 0;

    static const int aEditMode = 1;
};

class PdPatchPutMenu : public IUMenuBase {
public:
    virtual void draw() override;

    static const int aFileNew = 1;
};

class PdPatchArrangeMenu : public IUMenuBase {
public:
    virtual void draw() override;

    static const int aFileNew = 1;
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
