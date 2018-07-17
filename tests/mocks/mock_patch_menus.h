#ifndef MOCK_PATCH_MENUS_H
#define MOCK_PATCH_MENUS_H

PdPatchMenu::PdPatchMenu(PdCommonMenus*){};

void PdPatchArrangeMenu::_drawContents(){};
void PdPatchEditMenu::_drawContents(){};
void PdPatchPutMenu::_drawContents(){};

void PdPatchArrangeMenu::_shortcutContents(){};
void PdPatchEditMenu::_shortcutContents(){};
void PdPatchPutMenu::_shortcutContents(){};

#endif // MOCK_PATCH_MENUS_H
