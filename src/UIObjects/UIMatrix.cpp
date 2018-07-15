#include "UIMatrix.h"

UIMatrix::UIMatrix()
{
    observer.callback = [this]() {
        _value = std::stof(observer.data().getStringAt(0));
    };

    //    mouseDownAction = IUAction([&]() {
    //        if (pdObject)
    //            pdObject->sendBang();
    //    });
}

void UIMatrix::drawObjectContents()
{
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    //    if (_bangFrameCounter)
    //        draw_list->AddCircleFilled(ImVec2(x + width / 2, y + height / 2), width / 2 * .9, IM_COL32(0, 192, 255, 255), 24);

    //    draw_list->AddCircle(ImVec2(x + width / 2, y + height / 2), width / 2 * .9, IM_COL32(0, 192, 255, 255), 24, width / 20);

    //    if (_bangFrameCounter)
    //        _bangFrameCounter--;

    for (int i = 0; i < 5; i++) {
        draw_list->AddRect(ImVec2(x + width / 5 * i, y), ImVec2(x + width / 5 * (i + 1), y + height), IM_COL32(192, 192, 192, 255));
    }

    draw_list->AddRectFilled(ImVec2(x + 3 + width / 5 * _value, y + 3), ImVec2(x + width / 5 * (_value + 1) - 4, y + height - 4), IM_COL32(0, 192, 255, 255));
};

void UIMatrix::onMouseDown(ImVec2 pos)
{
    if (data.pdObject)
        data.pdObject->sendFloat((pos.x - x) / 25);
}

//void UIMatrix::_bang()
//{
//    _bangFrameCounter = 5;
//}
