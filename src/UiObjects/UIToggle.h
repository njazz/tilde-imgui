#ifndef UITOGGLE_H
#define UITOGGLE_H

#include "UIObjectBase.hpp"

class UIToggle : public UiObjectBase {
    bool _value = false;

public:
    UIToggle();

    virtual void draw() override
    {
        width = 25;
        height = 25;

        UiObjectBase::draw();
    };

    virtual void drawObjectContents() override
    {
        ImDrawList* draw_list = ImGui::GetWindowDrawList();

        if (_value) {
            draw_list->AddLine(ImVec2(x, y), ImVec2(x + width, y + height), IM_COL32(0, 192, 255, 255), width / 20);
            draw_list->AddLine(ImVec2(x + width, y), ImVec2(x, y + height), IM_COL32(0, 192, 255, 255), width / 20);
        }

    };

    virtual void onMouseDown(ImVec2 pos) override
    {
        _value = !_value;
        if (pdObject)
            pdObject->sendFloat(_value);
    }
};

#endif // UIBANG_H
