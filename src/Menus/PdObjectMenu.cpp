#include "PdObjectMenu.hpp"

void PdObjectMenu::_drawContents()
{
    item("Properties", aProperties, IUKey::Action() + IUKey::Shift() + IUKey::KeyP(), propertiesWindow);
    if (canvas)
    {
        ImGui::Separator();
        item("Open in new window");
        item("Open in new subwindow");
        item("Open in new tab");
    }
    ImGui::Separator();
    item("Help", aHelp);
}
