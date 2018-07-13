#include "UIMessage.h"

#include "IUWindowController.hpp"

int messageEdited(ImGuiTextEditCallbackData* o)
{
//    UIObject* obj = (UIObject*)o->UserData;

//    //obj->enteredText = std::string(o->BufTextLen, *o->Buf);
//    obj->enteredText = obj->_editText;
//    obj->updated(UIObject::oAutocomplete);

    // todo: width

    return 0;
}

UIMessage::UIMessage()
{
    _txtBuffer[0] = '\0';

    observer.callback = [this](){
        _contents = (observer.data().getStringAt(0));
    };
}

void UIMessage::_drawBackground()
{
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    draw_list->ChannelsSetCurrent(1);

    ImU32 borderColor = (this->data.selected) ? IM_COL32(0, 192, 255, 255) : IM_COL32(192, 192, 192, 255);

    if (data.errorBox)
        borderColor = IM_COL32(255, 0, 0, 255);
    if (data.emptyBox)
        borderColor = IM_COL32(0, 192, 255, 255);

    ImVec2 node_rect_min = ImVec2(this->x, this->y);
    ImVec2 node_rect_max = node_rect_min + ImVec2(width, height); //ImGui::GetItemRectMax();

    draw_list->ChannelsSetCurrent(0); // Background

    ImVec2 poly[6];

    poly[0] = ImVec2(x, y);
    poly[1] = ImVec2(x + width, y);
    poly[2] = ImVec2(x + width - 5, y + 5);
    poly[3] = ImVec2(x + width - 5, y + height - 5);
    poly[4] = ImVec2(x + width, y + height);
    poly[5] = ImVec2(x, y + height);
    //poly[6] = ImVec2(x, y);

    draw_list->AddConvexPolyFilled(poly, 6, IM_COL32(75, 75, 75, 255));
    draw_list->AddPolyline(poly, 6, borderColor, true, 1 + _mouseDown);

    _mouseDown = (ImGui::IsMouseDown(0) && ImGui::IsMouseHoveringRect(ImVec2(x, y), ImVec2(x + width, y + height)));
}

void UIMessage::drawObjectContents()
{
    ImGui::BeginGroup();
    ImGui::SetCursorScreenPos(ImVec2(x + 4, y + 4));
    if (_edit) {
        windowController()->isEditingText = true;


        if (ImGui::IsRootWindowOrAnyChildFocused() && !ImGui::IsAnyItemActive() && !ImGui::IsMouseClicked(0))
            ImGui::SetKeyboardFocusHere(0);


        if (ImGui::InputText("##in", _txtBuffer, 255, ImGuiInputTextFlags_CallbackAlways | ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll, &messageEdited, (void*)this)) {
            finishedEditingText();
        }


    } else {
        ImGui::Text("%s", _contents.c_str());
    }

    ImGui::EndGroup();
};

void UIMessage::finishedEditingText()
{
    std::string str = "set "+std::string(_txtBuffer);

    if (pdObject)
        pdObject->sendStringAsList(str);

    _edit = false;

    windowController()->restoreContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ClearInputCharacters();
    io.MouseDoubleClicked[0] = false;
    for (int i = 0; i < 512; i++)
        io.KeysDown[i] = false;
    windowController()->isEditingText = false;
}
