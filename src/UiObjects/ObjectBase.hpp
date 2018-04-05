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

#include "data_models/UIObjectData.h"


static inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y); }
static inline ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y); }

#include <functional>

class ObjectBaseObserver : public xpd::PdObjectObserver {

public:
    std::function <void(void)> callback = 0;

    virtual void update() override
    {
        printf("observer update\n");
        if (callback)
            callback();
    }
};

class ObjectBase : public IUView {
protected:
    void _drawInlet(int idx);
    void _drawOutlet(int idx);

    virtual void _drawBackground();

    std::string id() { return std::to_string((long)this); };

public:
    ObjectBase()
    {
        observer.callback = [this](){

            std::string d;
            if (observer.data().size())
                d = observer.data().getStringAt(0);

            for (int i=1; i<observer.data().size();i++)
                d += " + " + observer.data().getStringAt(i);

            printf("callback: %s\n",d.c_str());

        };
    }

    int inletCount = 0;
    int outletCount = 0;

    xpd::ObjectId pdObjectID = 0;
    xpd::PdObject* pdObject = 0;

    ObjectBaseObserver observer;

    virtual void draw() override;
    virtual void drawObjectContents(){};

    ImVec2 inletPos(int idx);
    ImVec2 outletPos(int idx);

    int inletType(int idx);
    int outletType(int idx);

    UIObjectData data;

    std::string objectText = "object";

    static const int oOutletClicked = 100;
    static const int oInletClicked = 101;
    static const int oInletHovered = 102;

    //
    void updateFromPdObject();
    void pdObjUpdatePosition();

    std::string asPdFileString();
};

#endif /* NodeObject_hpp */
