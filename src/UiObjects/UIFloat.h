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

    // temporary: fixed size
    virtual void draw() override;
    virtual void drawObjectContents() override;
    virtual void onMouseDrag(ImVec2 pos) override;
    virtual void onMouseUp(ImVec2 pos) override;
};

#endif // UIBANG_H
