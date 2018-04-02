//

#include "PdPatchMenu.hpp"

void PdPatchEditMenu::shortcuts()
{
    shortcut(aEditMode, IUKey::Action() + IUKey::KeyE());
}

void PdPatchEditMenu::draw()
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
    item("Edit mode", aEditMode, IUKey::Action() + IUKey::KeyE(), e);
}

void PdPatchPutMenu::shortcuts()
{
}

void PdPatchPutMenu::draw()
{
    ImGui::MenuItem("Object", "Cmd + 1");
    ImGui::MenuItem("Message", "Cmd + 2");
    ImGui::MenuItem("Comment", "Cmd + 5");
    ImGui::Separator();
    ImGui::MenuItem("Bang", "Cmd + Shift + B");
    ImGui::MenuItem("Toggle", "Cmd + Shift + T");
    ImGui::MenuItem("Number", "Cmd + 3");
}

void PdPatchArrangeMenu::shortcuts()
{
}
void PdPatchArrangeMenu::draw()
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
    ImGui::Separator();
    item("Align left", aAlignLeft);
    item("Align center", aAlignCenter);
    item("Align right", aAlignRight);
    ImGui::Separator();
    item("Align to top", aAlignTop);
    item("Align to botton", aAlignTop);
    ImGui::Separator();
    item("Distribute horizontally", aDistributeH);
    item("Distribute vertically", aDistributeV);
}

PdPatchMenu::PdPatchMenu(PdCommonMenus* m)
{
    // TODO
    common = new PdCommonMenus;
    //common = m;
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
