#include "Clipboard.h"
#include "IUView.hpp"
#include "UIObjectBase.hpp"
#include "UIPatchcord.hpp"



// ---

void IUBase::setWindowController(IUWindowController* w){};

IULayerBase::IULayerBase(){};

IULayer::IULayer() {}
void IULayer::draw() {}

IUView::IUView() {}
void IUView::_handleMouse() {}
void IUView::draw(){};
void IUView::removeFromParentView(){};

void IUMenuBase::draw() {}

void IUPopupMenu::draw() {}
