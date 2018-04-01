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

#include "ObjectBase.hpp"

class UIObject : public ObjectBase {

public:
    char* _editText = new char[128];

    std::string enteredText = "";

    bool _objectReplaceMode = false;

    virtual void draw() override;
    virtual void drawObjectContents() override;

    static const int oObjectChanged = 10;
    static const int oAutocomplete = 20;

    void clearEditText(){
        _editText[0] = '\0';
    }

    void finishedEditingText();

    //    static const int oSelected = 30;
};

#endif /* NodeObject_hpp */
