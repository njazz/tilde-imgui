#include "UIBang.h"

UIBang::UIBang()
{

}

 void UIBang::drawObjectContents()
{
    ImDrawList* draw_list = ImGui::GetWindowDrawList();


    if (ImGui::IsMouseDown(0) && ImGui::IsMouseHoveringRect(ImVec2(x,y), ImVec2(x+width,y+height)))
         draw_list->AddCircleFilled(ImVec2(x + width / 2, y +height / 2), width / 2 * .9, IM_COL32(0, 192, 255, 255), 24);

    draw_list->AddCircle(ImVec2(x + width / 2, y +height / 2), width / 2 * .9, IM_COL32(0, 192, 255, 255), 24, width/20);


    if (ImGui::IsMouseClicked(0) && ImGui::IsMouseHoveringRect(ImVec2(x,y), ImVec2(x+width,y+height)))
    {
        if (pdObject)
            pdObject->sendBang();
    }
};
