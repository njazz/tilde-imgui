#ifndef UIBANG_H
#define UIBANG_H

#include "UIObjectBase.hpp"

class UIBang : public UiObjectBase {
    int _bangFrameCounter = 0; // display when non-zero; decrement

    void _bang();
public:
    UIBang();

    virtual void draw() override
    {
        width = 25;
        height = 25;

        UiObjectBase::draw();
    };

    virtual void drawObjectContents() override;
};

#endif // UIBANG_H
