//

#include "IUMainMenuBase.hpp"
#include "PdCommonMenus.hpp"

class PdPatchEditMenu : public IUMenuBase {
public:
    virtual void draw() override
    {
        ImGui::MenuItem("Undo", "Cmd + Z");
        ImGui::MenuItem("Redo", "Cmd + Shift + Z");
        ImGui::Separator();
        ImGui::MenuItem("Cut", "Cmd + X");
        ImGui::MenuItem("Copy", "Cmd + C");
        ImGui::MenuItem("Paste", "Cmd + V");
        ImGui::Separator();
        ImGui::MenuItem("Select all", "Cmd + A");
        ImGui::Separator();
        ImGui::MenuItem("Delete selected", "Del");
        ImGui::Separator();

        bool e = (editModeFlag) ? *editModeFlag : false;
        item("Edit mode", aEditMode, IUKey::Action() + IUKey::C('E'), e);
    }

    bool* editModeFlag = 0;

    static const int aEditMode = 1;
};

class PdPatchPutMenu : public IUMenuBase {
public:
    virtual void draw() override
    {
        ImGui::MenuItem("Object", "Cmd + 1");
        ImGui::MenuItem("Message", "Cmd + 2");
        ImGui::MenuItem("Comment", "Cmd + 5");
        ImGui::Separator();
        ImGui::MenuItem("Bang", "Cmd + Shift + B");
        ImGui::MenuItem("Toggle", "Cmd + Shift + T");
        ImGui::MenuItem("Number", "Cmd + 3");
    }

    static const int aFileNew = 1;
};

class PdPatchArrangeMenu : public IUMenuBase {
public:
    virtual void draw() override
    {
        ImGui::MenuItem("Show grid");
        ImGui::MenuItem("Snap to grid");
        ImGui::Separator();
        ImGui::MenuItem("Align to grid");
        ImGui::MenuItem("Tidy up");
        ImGui::Separator();
        ImGui::MenuItem("Zoom in");
        ImGui::MenuItem("Zoom out");
        ImGui::MenuItem("Zoom 100%");
    }

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

    PdPatchMenu(PdCommonMenus* m)
    {
        common = new PdCommonMenus; // m;
        m = common;

        addMenu(&m->menuFile, "File");
        m->menuFile.inPatch = true;

        addMenu(&menuEdit, "Edit");
        addMenu(&menuPut, "Put");
        addMenu(&menuArrange, "Arrange");

        addMenu(&m->menuWindow, "Window");
        addMenu(&m->menuMedia, "Media");
        addMenu(&m->menuHelp, "Help");
    }
};
