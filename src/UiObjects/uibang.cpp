#include "UIBang.h"

UIBang::UIBang()
{
    observer.callback = [this]() {
        _bang();
    };
}

void UIBang::drawObjectContents()
{
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    //if (ImGui::IsMouseDown(0) && ImGui::IsMouseHoveringRect(ImVec2(x,y), ImVec2(x+width,y+height)))
    if (_bangFrameCounter)
        draw_list->AddCircleFilled(ImVec2(getX() + width / 2, getY() + height / 2), width / 2 * .9, IM_COL32(0, 192, 255, 255), 24);

    draw_list->AddCircle(ImVec2(getX() + width / 2, getY() + height / 2), width / 2 * .9, IM_COL32(0, 192, 255, 255), 24, width / 20);

    if (ImGui::IsMouseClicked(0) && ImGui::IsMouseHoveringRect(ImVec2(getX(), getY()), ImVec2(getX() + width, getY() + height))) {
        if (pdObject)
            pdObject->sendBang();
    }

    if (_bangFrameCounter)
        _bangFrameCounter--;
};

void UIBang::_bang()
{
    _bangFrameCounter = 5;
}
