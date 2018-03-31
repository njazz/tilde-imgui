#ifndef UITOGGLE_H
#define UITOGGLE_H

#include "ObjectBase.hpp"

class UIToggle : public ObjectBase {
    bool _value = false;

public:
    UIToggle();

    virtual void draw() override
    {

        width = 45;
        height = 45;

        ObjectBase::draw();
    };

    virtual void drawObjectContents() override
    {
        ImDrawList* draw_list = ImGui::GetWindowDrawList();

        //        if (ImGui::IsMouseDown(0) && ImGui::IsMouseHoveringRect(ImVec2(x,y), ImVec2(x+width,y+height)))
        //             draw_list->AddCircleFilled(ImVec2(x + width / 2, y +height / 2), width / 2 * .9, IM_COL32(0, 192, 255, 255), 24);

        if (_value){
        draw_list->AddLine(ImVec2(x, y), ImVec2(x + width, y + height), IM_COL32(0, 192, 255, 255), width / 20);
        draw_list->AddLine(ImVec2(x + width, y), ImVec2(x, y + height), IM_COL32(0, 192, 255, 255), width / 20);
        }

        if (ImGui::IsMouseClicked(0) && ImGui::IsMouseHoveringRect(ImVec2(x, y), ImVec2(x + width, y + height))) {
            _value = !_value;
            if (pdObject)
                pdObject->sendFloat(_value);
        }
    };
};

#endif // UIBANG_H
