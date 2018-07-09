#include "UIBang.h"

UIBang::UIBang()
{
    observer.callback = [this]() {
        _bang();
    };

//    mouseDownAction = IUAction([&]() {
//        if (pdObject)
//            pdObject->sendBang();
//    });
}

void UIBang::drawObjectContents()
{
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    if (_bangFrameCounter)
        draw_list->AddCircleFilled(ImVec2(x + width / 2, y + height / 2), width / 2 * .9, IM_COL32(0, 192, 255, 255), 24);

    draw_list->AddCircle(ImVec2(x + width / 2, y + height / 2), width / 2 * .9, IM_COL32(0, 192, 255, 255), 24, width / 20);

    if (_bangFrameCounter)
        _bangFrameCounter--;
};

void UIBang::onMouseDown(ImVec2 pos)
{
    if (pdObject)
        pdObject->sendBang();
}

void UIBang::_bang()
{
    _bangFrameCounter = 5;
}
