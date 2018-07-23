#ifndef MOCK_OBJECT_BASE_H
#define MOCK_OBJECT_BASE_H

#include "UIObjectBase.hpp"

void UiObjectBase::_drawBackground() {}
void UiObjectBase::draw() {}
UiObjectBase::UiObjectBase() :_propertiesWindow(data.properties(),&_patchMenu.propertiesWindow) {}
std::string UiObjectBase::asPdFileString() { return ""; }

#endif // MOCK_OBJECT_BASE_H
