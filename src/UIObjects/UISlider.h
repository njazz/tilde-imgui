#ifndef UISlider_H
#define UISlider_H

#include "UIObjectBase.hpp"

class UISlider : public UiObjectBase {
    float _value = 0.;

    float _rangeMin = 0.;
    float _rangeMax = 1.;
public:
    UISlider();

    // temporary fixed size:
    virtual void draw() override;

    virtual void drawObjectContents() override;

    virtual void onMouseDown(ImVec2 pos) override;
    virtual void onMouseDrag(ImVec2 pos) override;
};

#endif // UISlider_H
