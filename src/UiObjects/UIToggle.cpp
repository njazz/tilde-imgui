#include "UIToggle.h"

UIToggle::UIToggle()
{
    observer.callback = [this]() {
        _value = std::stoi(observer.data().getStringAt(0));
    };

    auto p = properties.create("Value","Slider","0.1",&_value);
//    p->componentAt(0).bindInt(&_value);
}

void UIToggle::draw()
{
    width = 25;
    height = 25;

    UiObjectBase::draw();
};

void UIToggle::drawObjectContents()
{
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    if (_value) {
        draw_list->AddLine(ImVec2(x, y), ImVec2(x + width, y + height), IM_COL32(0, 192, 255, 255), width / 20);
        draw_list->AddLine(ImVec2(x + width, y), ImVec2(x, y + height), IM_COL32(0, 192, 255, 255), width / 20);
    }
};

void UIToggle::onMouseDown(ImVec2 pos)
{
    _value = !_value;
    if (pdObject)
        pdObject->sendFloat(_value);
}
