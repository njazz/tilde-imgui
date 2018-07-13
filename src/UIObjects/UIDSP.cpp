#include "UIDSP.h"

UIDSP::UIDSP()
{
    observer.callback = [this]() {
//        _bang();
        _value = std::stof(observer.data().getStringAt(0));
    };

//    mouseDownAction = IUAction([&]() {
//        if (pdObject)
//            pdObject->sendBang();
//    });
}

void UIDSP::drawObjectContents()
{
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

//    if (_bangFrameCounter)

    if (_value)
        draw_list->AddCircleFilled(ImVec2(x + width / 2, y + height / 2), width / 2 * .9, IM_COL32(0, 192, 255, 255), 24);


    draw_list->AddText(ImGui::GetFont(),16,ImVec2(x + width / 2-12, y + height / 2-8),IM_COL32(255,255,255,255),"DSP");
    draw_list->AddCircle(ImVec2(x + width / 2, y + height / 2), width / 2 * .9, IM_COL32(0, 192, 255, 255), 24, width / 20);

//    if (_bangFrameCounter)
//        _bangFrameCounter--;
};

void UIDSP::onMouseDown(ImVec2 pos)
{
    if (pdObject)

        pdObject->sendStringAsList((_value)?"dsp 0":"dsp 1");
}

//void UIDSP::_bang()
//{
//    _bangFrameCounter = 5;
//}
