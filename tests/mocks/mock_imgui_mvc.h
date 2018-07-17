#include "Clipboard.h"
#include "IUView.hpp"
#include "UIObjectBase.hpp"
#include "UIPatchcord.hpp"

#include "imgui.h"

// ---

// duplicate in 'imgui_mock.cpp':
ImGuiIO _io;
namespace ImGui {
ImGuiIO& GetIO() { return _io; }
}

ImGuiIO::ImGuiIO(){}
// ---

// !! **** IUAction
IUAction::IUAction(std::function<void ()> fn){
    _callback = fn;
}

void IUBase::setWindowController(IUWindowController* w){_windowController = w;};
IUWindowController* IUBase::windowController() {return _windowController;}

IULayerBase::IULayerBase(){};

IULayer::IULayer() {}
void IULayer::draw() {}

IUView::IUView() {}
void IUView::_handleMouse() {}
void IUView::draw(){};
void IUView::removeFromParentView(){};

void IUMainMenuBase::draw() {}

void IUMenuBase::draw() {}

void IUPopupMenu::draw() {}

void IUViewControllerBase::draw(){}
void IUViewControllerBase::drawMenu(){}

void IUWindowController::restoreContext(){}

// ?


