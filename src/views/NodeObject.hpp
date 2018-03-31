//
//  NodeObject.hpp
//  nseq
//
//  Created by Alex on 23/03/2018.
//  Copyright © 2018 Alex Nadzharov. All rights reserved.
//

#ifndef NodeObject_hpp
#define NodeObject_hpp

#include <stdio.h>

#include "IUView.hpp"
#include "imgui.h"

#include <string>

#include "pd_object.h"

#include "NodeBaseObject.hpp"

//static inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y); }
//static inline ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y); }

//class ObjectBase : public IUView {
//protected:
//    inline void _drawInlet(int idx);
//    inline void _drawOutlet(int idx);

//public:
//    xpd::ObjectId pdObjectID = 0;
//    xpd::PdObject* pdObject = 0;

//    virtual void draw() override{};

//    int inletCount = 2;
//    int outletCount = 1;

//    ImVec2 inletPos(int idx);
//    ImVec2 outletPos(int idx);
//};

class NodeObject : public ObjectBase {
    std::string id() { return std::to_string((long)this); };

    char* _editText = new char[128];

public:
    bool _objectReplaceMode = false;


    xpd::ObjectId pdObjectID = 0;
    xpd::PdObject* pdObject = 0;



    bool selected = false;

    virtual void draw() override;

    static const int oObjectChanged = 10;
    static const int oAutocomplete = 20;

    //    static const int oSelected = 30;
};

#endif /* NodeObject_hpp */
