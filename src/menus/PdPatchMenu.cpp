//

#include "PdPatchMenu.hpp"

void PdPatchEditMenu::shortcuts()
{
    shortcut(aEditMode, IUKey::Action() + IUKey::KeyE());

    if (editModeFlag)
        if (*editModeFlag) {
            shortcut(aCut, IUKey::Action() + IUKey::KeyX());
            shortcut(aCopy, IUKey::Action() + IUKey::KeyC());
            shortcut(aPaste, IUKey::Action() + IUKey::KeyV());

            shortcut(aSelectAll, IUKey::Action() + IUKey::KeyA());

            shortcut(aDelete, IUShortcut(IUKey::Delete()));
            shortcut(aDelete, IUShortcut(IUKey::Backspace()));
        }
}

void PdPatchEditMenu::drawContents()
{
    if (editModeFlag)
        if (*editModeFlag) {
            // todo: action names
            item("Undo", aUndo, IUKey::Action() + IUKey::KeyZ());
            item("Redo", aUndo, IUKey::Action() + IUKey::Shift() + IUKey::KeyZ());
            ImGui::Separator();
            item("Cut", aCut, IUKey::Action() + IUKey::KeyX());
            item("Copy", aCopy, IUKey::Action() + IUKey::KeyC());
            item("Paste", aPaste, IUKey::Action() + IUKey::KeyV());
            ImGui::Separator();
            item("Select all", aSelectAll, IUKey::Action() + IUKey::KeyA());
            ImGui::Separator();
            item("Delete selected", aDelete, IUShortcut(IUKey::Delete()));
            ImGui::Separator();
        }

    bool e = (editModeFlag) ? *editModeFlag : false;
    item("Edit mode", aEditMode, IUKey::Action() + IUKey::KeyE(), e);
}

void PdPatchPutMenu::shortcuts()
{
}

void PdPatchPutMenu::drawContents()
{
    item("Object", aObject, IUKey::Action() + IUKey::Key1());
    item("Message", aMessage, IUKey::Action() + IUKey::Key2());
    item("Comment", aComment, IUKey::Action() + IUKey::Key5());
    ImGui::Separator();
    item("Bang", aBang, IUKey::Action() + IUKey::Shift() + IUKey::KeyB());
    item("Toggle", aToggle, IUKey::Action() + IUKey::Shift() + IUKey::KeyT());
    item("Number", aNumber, IUKey::Action() + IUKey::Key3());
    ImGui::Separator();
    item("Slider", aSlider, IUKey::Action() + IUKey::Shift() + IUKey::KeyV());
    item("Knob");
    item("Slider2D");
    item("Range Slider");
    item("Sliders");
    item("Matrix Buttons");
    item("Radio Buttons", aRadioButtons, IUKey::Action() + IUKey::Shift() + IUKey::KeyD());
    ImGui::Separator();
    item("Array", aArray, IUKey::Action() + IUKey::Shift() + IUKey::KeyA());
    ImGui::Separator();
    item("Keyboard");
    item("Envelope");
    item("Display");
    ImGui::Separator();
    item("Scope");
    item("Spectroscope");
    //ImGui::Separator();
}

void PdPatchArrangeMenu::shortcuts()
{
}
void PdPatchArrangeMenu::drawContents()
{
    bool sh = (showGrid) ? *showGrid : false;
    bool sg = (snapToGrid) ? *snapToGrid : false;

    if (item("Show grid", 0, IUKey::Action() + IUKey::Shift()+IUKey::KeyG(), sh)) {
        if (showGrid)
            *showGrid = !*showGrid;
    }
    if (item("Snap to grid", 0, IUKey::Alt()+IUKey::KeyG(), sg)) {
        if (snapToGrid)
            *snapToGrid = !*snapToGrid;
    }
    ImGui::Separator();
    ImGui::MenuItem("Align to grid");
    ImGui::MenuItem("Tidy up");
    ImGui::Separator();
    item("Zoom In", aZoomIn, IUKey::Action() + IUKey::Equal());
    item("Zoom Out", aZoomOut, IUKey::Action() + IUKey::Minus());
    item("Zoom 100%", aZoomOne, IUKey::Action() + IUKey::Key0());
    ImGui::Separator();
    item("Align left", aAlignLeft, IUKey::Action() + IUKey::Shift() + IUKey::Left());
    item("Align center", aAlignCenter);
    item("Align right", aAlignRight, IUKey::Action() + IUKey::Shift() + IUKey::Right());
    ImGui::Separator();
    item("Align to top", aAlignTop, IUKey::Action() + IUKey::Shift() + IUKey::Up());
    item("Align to botton", aAlignBottom, IUKey::Action() + IUKey::Shift() + IUKey::Down());
    ImGui::Separator();
    item("Distribute horizontally", aDistributeH);
    item("Distribute vertically", aDistributeV);
}

PdPatchMenu::PdPatchMenu(PdCommonMenus* m)
{
    // TODO
    common = new PdCommonMenus;
    //common = m;

    common->menuFile.copyActionsFrom(&m->menuFile);
    common->menuMedia.copyActionsFrom(&m->menuMedia);
    common->menuWindow.copyActionsFrom(&m->menuWindow);
    common->menuHelp.copyActionsFrom(&m->menuHelp);

    //    m = common;

    addMenu(&common->menuFile, "File");
    common->menuFile.inPatch = true;

    addMenu(&menuEdit, "Edit");
    addMenu(&menuPut, "Put");
    addMenu(&menuArrange, "Arrange");

    addMenu(&common->menuWindow, "Window");
    addMenu(&common->menuMedia, "Media");
    addMenu(&common->menuHelp, "Help");
}

void PdObjectMenu::drawContents()
{
    item("Properties", aProperties, IUKey::Action() + IUKey::Shift() + IUKey::KeyP(), propertiesWindow);
    ImGui::Separator();
    item("Help", aHelp);
}
