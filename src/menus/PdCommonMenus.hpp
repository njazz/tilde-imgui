//

#ifndef PdCommonMenu_hpp
#define PdCommonMenu_hpp

#include "IUMenuBase.hpp"

class PdCommonFileMenu : public IUMenuBase {
public:
    bool inPatch;

    virtual void shortcuts() override;
    virtual void drawContents() override;

    static const int aFileNew = 1;
    static const int aFileOpen = 2;
    static const int aFileSave = 3;
    static const int aFileSaveAs = 4;
    static const int aFileClose = 5;
    static const int aFileQuit = 10;
};

class PdCommonWindowMenu : public IUMenuBase {

public:
    virtual void shortcuts() override;
    virtual void drawContents() override;

    static const int aSettings = 1;
    static const int aAudioMIDI = 2;
    static const int aClearConsole = 3;
};

class PdCommonMediaMenu : public IUMenuBase {
public:
    bool* dspOn = 0;

    virtual void shortcuts() override;
    virtual void drawContents() override;

    static const int aDSPOn = 1;
    static const int aDSPOff = 2;
};

class PdCommonHelpMenu : public IUMenuBase {
    virtual void drawContents() override;

    static const int aHelp = 1;
};

struct PdCommonMenus
{
    PdCommonFileMenu menuFile;
    PdCommonMediaMenu menuMedia;
    PdCommonWindowMenu menuWindow;
    PdCommonHelpMenu menuHelp;

    void setWindowController(IUWindowController* w);
};

#endif
