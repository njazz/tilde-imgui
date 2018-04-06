#ifndef UIFloat_H
#define UIFloat_H

#include "ObjectBase.hpp"
#include <string>

class UIFloat : public ObjectBase {

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

        ObjectBase::draw();
    };

    virtual void drawObjectContents() override
    {
        //ImDrawList* draw_list = ImGui::GetWindowDrawList();

        ImGui::BeginGroup();
        ImGui::SetCursorScreenPos(ImVec2(getX() + 4, getY() + 4));
        ImGui::Text("%f", _value);
        ImGui::EndGroup();

        if (ImGui::IsMouseClicked(0) && ImGui::IsMouseHoveringRect(ImVec2(getX(), getY()), ImVec2(getX() + width, getY() + height))) {
            //            _value = !_value;
            //            if (pdObject)
            //                pdObject->sendFloat(_value);
        }
    };
};

#endif // UIBANG_H
