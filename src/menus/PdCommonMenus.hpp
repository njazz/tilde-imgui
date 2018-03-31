//

#ifndef PdCommonMenu_hpp
#define PdCommonMenu_hpp

#include "IUMenuBase.hpp"

class PdCommonFileMenu : public IUMenuBase {
public:
    bool inPatch;

    virtual void draw() override
    {
        item("New patch window", aFileNew, IUKey::Action() + IUKey::C('N'));
        ImGui::Separator();
        item("Open patch in new window", aFileOpen, IUKey::Action() + IUKey::C('O'));
        if (inPatch) {
            item("Save patch", aFileSave, IUKey::Action() + IUKey::C('S'));
            item("Save patch as ...", aFileSaveAs, IUKey::Action() + IUKey::Shift() + IUKey::C('N'));
        }
        ImGui::Separator();
        item("Quit", aFileExit, IUKey::Action() + IUKey::C('Q'));
    }

    static const int aFileNew = 1;
    static const int aFileOpen = 2;
    static const int aFileSave = 3;
    static const int aFileSaveAs = 4;
    static const int aFileExit = 10;
};

class PdCommonWindowMenu : public IUMenuBase {

public:
    virtual void draw() override
    {
        item("Settings ...", aSettings);
        item("Audio / MIDI setup...", aAudioMIDI);
        ImGui::Separator();
        item("Clear console", aClearConsole, IUKey::Action() + IUKey::Shift() + IUKey::C('L'));
    }

    static const int aSettings = 1;
    static const int aAudioMIDI = 2;
    static const int aClearConsole = 3;
};

class PdCommonMediaMenu : public IUMenuBase {
public:
    bool* dspOn = 0;

    virtual void draw() override
    {
        bool v;
        if (!dspOn)
            v = false;
        else
            v = *dspOn;
        item("DSP On", aDSPOn, IUKey::Action() + IUKey::C('/'), v);
        item("DSP Off", aDSPOff, IUKey::Action() + IUKey::C('.'), !v);
    }

    static const int aDSPOn = 1;
    static const int aDSPOff = 2;
};

class PdCommonHelpMenu : public IUMenuBase {
    virtual void draw() override
    {
        item("Pd Help", aHelp);
    }

    static const int aHelp = 1;
};

struct PdCommonMenus
{
    PdCommonFileMenu menuFile;
    PdCommonMediaMenu menuMedia;
    PdCommonWindowMenu menuWindow;
    PdCommonHelpMenu menuHelp;
};

#endif
