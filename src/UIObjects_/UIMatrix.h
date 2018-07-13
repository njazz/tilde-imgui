#ifndef UIMatrix_H
#define UIMatrix_H

#include "UIObjectBase.hpp"

class UIMatrix : public UiObjectBase {
    int _bangFrameCounter = 0; // display when non-zero; decrement

//    void _bang();

    float _value = 0;
public:
    UIMatrix();

    // temporary fixed size:
    virtual void draw() override
    {
        width = 125;
        height = 25;

        UiObjectBase::draw();
    };

    virtual void drawObjectContents() override;

    virtual void onMouseDown(ImVec2 pos) override ;
};

#endif // UIMatrix_H
