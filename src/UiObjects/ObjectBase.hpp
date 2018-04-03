//
//  NodeObject.hpp
//  nseq
//
//  Created by Alex on 23/03/2018.
//  Copyright © 2018 Alex Nadzharov. All rights reserved.
//

#ifndef NodeBaseObject_hpp
#define NodeBaseObject_hpp

#include <stdio.h>

#include "IUView.hpp"
#include "imgui.h"

#include <string>

#include "pd_object.h"

static inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y); }
static inline ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y); }

class ObjectBase : public IUView {
protected:
    void _drawInlet(int idx);
    void _drawOutlet(int idx);

    virtual void _drawBackground();

    std::string id() { return std::to_string((long)this); };

public:
    xpd::ObjectId pdObjectID = 0;
    xpd::PdObject* pdObject = 0;

    virtual void draw() override;
    virtual void drawObjectContents(){};

    int inletCount = 0;
    int outletCount = 0;

    ImVec2 inletPos(int idx);
    ImVec2 outletPos(int idx);

    int inletType(int idx);
    int outletType(int idx);

    std::string objectText = "object";

    bool errorBox = false;
    bool emptyBox = false;
    bool selected = false;

    int outletClicked = -1;
    int inletClicked = -1;

    static const int oOutletClicked = 100;
    static const int oInletClicked = 101;
    static const int oInletHovered = 102;

    //
    void updateFromPdObject()
    {
        errorBox = (pdObject == 0);

        if (pdObject) {
            inletCount = pdObject->inletCount();
            outletCount = pdObject->outletCount();
            std::string info = objectText + " ins: " + std::to_string(inletCount) + " outs:" + std::to_string(outletCount);
        }
    }

    void pdObjUpdatePosition()
    {
        if (!pdObject)
            return;
        pdObject->setX(x);
        pdObject->setY(y);
    }

    std::string asPdFileString()
    {
        return "#X obj " + std::to_string(x) + " " + std::to_string(y) + " " + objectText;
    }
};

#endif /* NodeObject_hpp */
