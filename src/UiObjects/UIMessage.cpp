#include "UIMessage.h"

UIMessage::UIMessage()
{
}

void UIMessage::_drawBackground()
{
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    draw_list->ChannelsSetCurrent(1);

    ImU32 borderColor = (this->selected) ? IM_COL32(0, 192, 255, 255) : IM_COL32(192, 192, 192, 255);

    if (errorBox)
        borderColor = IM_COL32(255, 0, 0, 255);
    if (emptyBox)
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
    poly[6] = ImVec2(x, y);

    draw_list->AddConvexPolyFilled(poly, 6, IM_COL32(75, 75, 75, 255));
    draw_list->AddPolyline(poly, 6, borderColor, true, 1 + _mouseDown);

    _mouseDown = (ImGui::IsMouseDown(0) && ImGui::IsMouseHoveringRect(ImVec2(x, y), ImVec2(x + width, y + height)));


}
