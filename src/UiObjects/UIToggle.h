#ifndef UITOGGLE_H
#define UITOGGLE_H

#include "UIObjectBase.hpp"

class UIToggle : public UiObjectBase {
    bool _value = 0;

public:
    UIToggle();

    virtual void draw() override;
    virtual void drawObjectContents() override;
    virtual void onMouseDown(ImVec2 pos) override;
};

#endif // UIBANG_H
