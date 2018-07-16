#include "Clipboard.h"
#include "IUView.hpp"
#include "UIObjectBase.hpp"
#include "UIPatchcord.hpp"





void PdObjectMenu::_drawContents(){}

void UIPropertiesWindow::_drawContents(){};

void UiObjectBase::_drawBackground() {}
void UiObjectBase::draw() {}
UiObjectBase::UiObjectBase() :_propertiesWindow(data.properties(),&_patchMenu.propertiesWindow) {}
std::string UiObjectBase::asPdFileString() { return ""; }

UIPropertiesWindow::UIPropertiesWindow(PropertyList *p, bool *d){}

void UIPatchcord::_drawContents(){}
// ---

class TestObject : public UiObjectBase
{};

