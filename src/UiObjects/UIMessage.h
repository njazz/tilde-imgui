#ifndef UIMessage_H
#define UIMessage_H

#include "UIObjectBase.hpp"
#include <string>

class UIMessage : public UiObjectBase {
    //bool _value = false;

    std::string _contents = "msg";

    virtual void _drawBackground() override;

    bool _mouseDown = false;

    bool _edit = false;
    char _txtBuffer[256];
public:
    UIMessage();

    virtual void draw() override
    {

        width = 60;
        height = 30;

        UiObjectBase::draw();
    };

    virtual void drawObjectContents() override;

    virtual void onMouseDoubleClickEdited(ImVec2 pos) override
    {
        _edit = !_edit;
    }

    void finishedEditingText();
};

#endif // UIBANG_H
