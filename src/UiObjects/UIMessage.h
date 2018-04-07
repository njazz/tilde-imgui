#ifndef UIMessage_H
#define UIMessage_H

#include "ObjectBase.hpp"
#include <string>

class UIMessage : public ObjectBase {
    //bool _value = false;

    std::string _contents = "msg";

    virtual void _drawBackground() override;

    bool _mouseDown = false;
public:
    UIMessage();

    virtual void draw() override
    {

        width = 60;
        height = 30;

        ObjectBase::draw();
    };

    virtual void drawObjectContents() override
    {
        ImDrawList* draw_list = ImGui::GetWindowDrawList();

        ImGui::BeginGroup();
        ImGui::SetCursorScreenPos(ImVec2(x+4,y+4));
        ImGui::Text("%s",_contents.c_str());
        ImGui::EndGroup();

        if (ImGui::IsMouseClicked(0) && ImGui::IsMouseHoveringRect(ImVec2(x, y), ImVec2(x + width, y + height))) {
//            _value = !_value;
//            if (pdObject)
//                pdObject->sendFloat(_value);
        }
    };
};

#endif // UIBANG_H
