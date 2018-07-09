#ifndef UISlider_H
#define UISlider_H

#include "UIObjectBase.hpp"

class UISlider : public UiObjectBase {
    int _bangFrameCounter = 0; // display when non-zero; decrement

//    void _bang();

    float _value = 0.;
public:
    UISlider();

    // temporary fixed size:
    virtual void draw() override
    {
        width = 25;
        height = 100;

        UiObjectBase::draw();
    };

    virtual void drawObjectContents() override;

    virtual void onMouseDown(ImVec2 pos) override ;

    virtual void onMouseDrag(ImVec2 pos) override
    {
        float prevValue = _value;
        _value -= pos.y / 100.;
        if (pdObject)
            if (prevValue != _value)
            pdObject->sendFloat(_value);
    }
};

#endif // UISlider_H
