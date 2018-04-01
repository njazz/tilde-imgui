#ifndef UIBANG_H
#define UIBANG_H

#include "ObjectBase.hpp"

class UIBang : public ObjectBase {
public:
    UIBang();

    virtual void draw() override
    {
        width = 45;
        height = 45;

        ObjectBase::draw();
    };

    virtual void drawObjectContents() override;
};

#endif // UIBANG_H
