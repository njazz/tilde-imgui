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

class NodeObject : public ObjectBase {

    char* _editText = new char[128];

public:
    bool _objectReplaceMode = false;

    xpd::ObjectId pdObjectID = 0;
    xpd::PdObject* pdObject = 0;


    virtual void draw() override;

    static const int oObjectChanged = 10;
    static const int oAutocomplete = 20;

    //    static const int oSelected = 30;
};

#endif /* NodeObject_hpp */
