#ifndef UIFloat_H
#define UIFloat_H

#include "UIObjectBase.hpp"
#include <string>

class UIFloat : public UiObjectBase {

    //std::string _contents = "0.";

    virtual void _drawBackground() override;

    bool _mouseDown = false;

    float _value = 0.;

public:
    UIFloat();

    virtual void draw() override
    {

        width = 50;
        height = 25;

        UiObjectBase::draw();
    };

    virtual void drawObjectContents() override
    {
        //ImDrawList* draw_list = ImGui::GetWindowDrawList();

        ImGui::BeginGroup();
        ImGui::SetCursorScreenPos(ImVec2(x + 4, y + 4));
        ImGui::Text("%f", _value);
        ImGui::EndGroup();

        if (ImGui::IsMouseClicked(0) && ImGui::IsMouseHoveringRect(ImVec2(x, y), ImVec2(x + width, y + height))) {
            //            _value = !_value;
            //            if (pdObject)
            //                pdObject->sendFloat(_value);
        }
    };
};

#endif // UIBANG_H
