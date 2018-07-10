#include "UISlider.h"

UISlider::UISlider()
{

    observer.callback = [this]() {
        _value = std::stof(observer.data().getStringAt(0));
        if (_value < _rangeMin)
            _value = _rangeMin;
        if (_value > _rangeMax)
            _value = _rangeMax;
    };

    Property* p = properties.create("Range Min","Slider","0.1",0.);
    p->componentAt(0).bindFloat(&_rangeMin);

    p = properties.create("Range Max","Slider","0.1",1.);
    p->componentAt(0).bindFloat(&_rangeMax);

    p = properties.create("Value","Slider","0.1",0.);
    p->componentAt(0).bindFloat(&_value);

}

 void UISlider::draw()
{
    width = 25;
    height = 100;

    UiObjectBase::draw();
};


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

 void UISlider::onMouseDrag(ImVec2 pos)
{
    float prevValue = _value;
    _value -= pos.y / 100.;
    if (pdObject)
        if (prevValue != _value)
        pdObject->sendFloat(_value);
}

//void UISlider::_bang()
//{
//    _bangFrameCounter = 5;
//}
