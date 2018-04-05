#ifndef UIBANG_H
#define UIBANG_H

#include "ObjectBase.hpp"

class UIBang : public ObjectBase {
    int _bangFrameCounter = 0; // display when non-zero; decrement

    void _bang();
public:
    UIBang();

    virtual void draw() override
    {
        width = 25;
        height = 25;

        ObjectBase::draw();
    };

    virtual void drawObjectContents() override;
};

#endif // UIBANG_H
