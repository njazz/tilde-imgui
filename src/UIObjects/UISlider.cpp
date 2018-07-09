#include "UISlider.h"

UISlider::UISlider()
{
    observer.callback = [this]() {
        _value = std::stof(observer.data().getStringAt(0));
        if (_value < 0)
            _value = 0;
        if (_value > 1)
            _value = 1;
    };

    //    mouseDownAction = IUAction([&]() {
    //        if (pdObject)
    //            pdObject->sendBang();
    //    });
}

void UISlider::drawObjectContents()
{
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    draw_list->AddRectFilled(ImVec2(x, y + height), ImVec2(x + width, y + height * (1 - _value)), IM_COL32(0, 192, 255, 255));
};

void UISlider::onMouseDown(ImVec2 pos)
{
//    if (pdObject)
//        pdObject->sendBang();

    _value = 1- ((pos.y-y) / 100.);
    if (pdObject)
        pdObject->sendFloat(_value);
}

//void UISlider::_bang()
//{
//    _bangFrameCounter = 5;
//}
