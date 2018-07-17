#include "Clipboard.h"
#include "IUView.hpp"
#include "UIObjectBase.hpp"
#include "UIPatchcord.hpp"

#include "imgui.h"

#include "nfd.h"
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

// EXTRAS

void ImDrawList::AddRectFilled(const ImVec2 &a, const ImVec2 &b, ImU32 col, float rounding, int rounding_corners_flags){};

void ImGui::SetTooltip(char const*, ...) {};
ImVec2 ImGui::GetMousePos() {return ImVec2(11,11);};
void ImGui::PopStyleVar(int v) {};

void ImGui::PushStyleVar(ImGuiStyleVar idx, const ImVec2 &val){}
void ImGui::SetCursorPos(const ImVec2 &local_pos){};
void ImGui::EndChildFrame() {}
bool ImGui::IsMouseClicked(int button, bool repeat){return false;};
bool ImGui::BeginChildFrame(ImGuiID id, const ImVec2 &size, ImGuiWindowFlags flags){return false;}
bool ImGui::IsMouseReleased(int button){return false;}
ImDrawList* ImGui::GetWindowDrawList() {return 0;}
ImGuiID ImGui::GetID(const char *str_id) {
    ImGuiID id;
    return id;
};
bool ImGui::MenuItem(const char *label, const char *shortcut, bool *p_selected, bool enabled) {return false;};
bool ImGui::MenuItem(const char *label, const char *shortcut, bool selected, bool enabled){return false;};

// =======

void IUBase::setWindowController(IUWindowController* w){_windowController = w;};
IUWindowController* IUBase::windowController() {return _windowController;}

IULayerBase::IULayerBase(){};

IULayer::IULayer() {}
void IULayer::draw() {}

IUView::IUView() {}
void IUView::_handleMouse() {}
void IUView::draw(){};
void IUView::removeFromParentView(){};

void IUView::addSubview(IUView *v){};
void IUView::setUserObjectForAction(int k, void *obj){};
void IUView::updated(int key){};
void IUView::addAction(int k, IUAction *o){};

void IUMainMenuBase::draw() {}
void IUMainMenuBase::addMenu(IUMenuBase *m, std::string name){}

void IUMenuBase::draw() {}

void IUPopupMenu::draw() {}

void IUViewControllerBase::draw(){}
void IUViewControllerBase::drawMenu(){}

IUWindowController::IUWindowController(IUViewControllerBase *vc, std::string title, int x, int y, int width, int height){}
void IUWindowController::restoreContext(){}

// ?

//
nfdresult_t NFD_SaveDialog(const nfdchar_t *filterList, const nfdchar_t *defaultPath, nfdchar_t **outPath){return NFD_OKAY; };
nfdresult_t NFD_OpenDialog(const nfdchar_t *filterList, const nfdchar_t *defaultPath, nfdchar_t **outPath){return NFD_OKAY;};

//
void glfwSetWindowShouldClose(GLFWwindow *window, int value){};

