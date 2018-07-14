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

#include "UIObjectData.h"

#include "PdPatchMenu.hpp"
#include "PdObjectMenu.hpp"

#include "UIPropertiesWindow.hpp"

static inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y); }
static inline ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y); }

#include <functional>

class ObjectBaseObserver : public xpd::PdObjectObserver {

public:
    std::function<void(void)> callback = 0;

    virtual void update() override
    {
        printf("observer update\n");
        if (callback)
            callback();
    }
};

class UiObjectBase : public IUView {
private:
    PdObjectMenu _patchMenu;
    UIPropertiesWindow _propertiesWindow;

protected:
    void _drawInlet(int idx);
    void _drawOutlet(int idx);

    virtual void _drawBackground();

    std::string id() { return std::to_string((long)this); };

    void _createProperties();

    // temporary?
    bool _mouseDownFlag = false;

    bool _showPropertiesWindow = false;
public:    
    UIObjectData data = UIObjectData();

//    PropertyList properties;

//    int inletCount = 0;
//    int outletCount = 0;

    xpd::ObjectId pdObjectID = 0;
    xpd::PdObject* pdObject = 0;

    ObjectBaseObserver observer;

//
    UiObjectBase();

    virtual void draw() override;
    virtual void drawObjectContents(){};

    ImVec2 inletPos(int idx);
    ImVec2 outletPos(int idx);

    int inletType(int idx);
    int outletType(int idx);

    std::string objectText = "object";

    //
    static const int oOutletClicked = 100;
    static const int oInletClicked = 101;
    static const int oInletHovered = 102;

    static const int oOpenCanvas = 200;

    static const int oOpenHelp = 300;

    //
    void updateFromPdObject();
    void pdObjUpdatePosition();

    std::string asPdFileString();

    //
    bool* editModePtr = 0;

    //
    virtual void onMouseDown(ImVec2 pos) override{};
    virtual void onMouseHover(ImVec2 pos) override{};
    virtual void onMouseUp(ImVec2 pos) override {};
    virtual void onMouseDrag(ImVec2 pos) override{};

    virtual void onMouseDoubleClick(ImVec2 pos) override{};
    virtual void onMouseRightClick(ImVec2 pos) override{};

    virtual void onMouseDoubleClickEdited(ImVec2 pos) {};
};

#endif /* NodeObject_hpp */
