#ifndef UIDSP_H
#define UIDSP_H

#include "UIObjectBase.hpp"

class UIDSP : public UiObjectBase {
    int _bangFrameCounter = 0; // display when non-zero; decrement

    void _bang();

    float _value = 0;
public:
    UIDSP();

    virtual void draw() override
    {
        // temporary fixed size:
        width = 50;
        height = 50;

        UiObjectBase::draw();
    };

    virtual void drawObjectContents() override;

    virtual void onMouseDown(ImVec2 pos) override ;
};

#endif // UIDSP_H
