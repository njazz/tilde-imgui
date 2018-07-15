#include "UIFloat.h"

UIFloat::UIFloat()
{
    observer.callback = [this](){
        _value = std::stof(observer.data().getStringAt(0));
    };
}

void UIFloat::_drawBackground()
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
    poly[1] = ImVec2(x + width-5, y);
    poly[2] = ImVec2(x + width, y + 5);
    poly[3] = ImVec2(x + width, y + height);
    poly[4] = ImVec2(x, y + height);
    poly[5] = ImVec2(x, y);

    draw_list->AddConvexPolyFilled(poly, 5, IM_COL32(75, 75, 75, 255));
    draw_list->AddPolyline(poly, 5, borderColor, true, 1 + _mouseDown);

//    _mouseDown = (ImGui::IsMouseDown(0) && ImGui::IsMouseHoveringRect(ImVec2(x, y), ImVec2(x + width, y + height)));


}

 void UIFloat::drawObjectContents()
{
    //ImDrawList* draw_list = ImGui::GetWindowDrawList();

    ImGui::BeginGroup();
    ImGui::SetCursorScreenPos(ImVec2(x + 4, y + 4));
    ImGui::Text("%0.2f", _value);
    ImGui::EndGroup();

    if (ImGui::IsMouseClicked(0) && ImGui::IsMouseHoveringRect(ImVec2(x, y), ImVec2(x + width, y + height))) {
        //            _value = !_value;
        //            if (pdObject)
        //                pdObject->sendFloat(_value);
    }
};

  void UIFloat::draw()
 {

     width = 50;
     height = 25;

     UiObjectBase::draw();
 };

 void UIFloat::onMouseDrag(ImVec2 pos)
 {
     _value -= pos.y / 10;
     if (data.pdObject)
         data.pdObject->sendFloat(_value);

     _mouseDown = true;
 }

 void UIFloat::onMouseUp(ImVec2 pos)
 {
     _mouseDown = false;
 }
