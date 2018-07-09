#ifndef UIBANG_H
#define UIBANG_H

#include "UIObjectBase.hpp"

class UIBang : public UiObjectBase {
    int _bangFrameCounter = 0; // display when non-zero; decrement

    void _bang();
public:
    UIBang();

    // temporary fixed size:
    virtual void draw() override
    {
        width = 25;
        height = 25;

        UiObjectBase::draw();
    };

    virtual void drawObjectContents() override;

    virtual void onMouseDown(ImVec2 pos) override ;
};

#endif // UIBANG_H
