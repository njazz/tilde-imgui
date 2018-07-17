#ifndef MOCK_COMMON_MENUS_H
#define MOCK_COMMON_MENUS_H

#include "PdCommonMenus.hpp"

void PdCommonFileMenu::_drawContents() {}
void PdCommonHelpMenu::_drawContents() {}
void PdCommonMediaMenu::_drawContents() {}
void PdCommonWindowMenu::_drawContents() {}

void PdCommonFileMenu::_shortcutContents() {}
//void PdCommonHelpMenu::_shortcutContents(){}
void PdCommonMediaMenu::_shortcutContents() {}
void PdCommonWindowMenu::_shortcutContents() {}

void PdCommonMenus::setWindowController(IUWindowController* w){};

#endif // MOCK_COMMON_MENUS_H
