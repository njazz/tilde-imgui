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

#include "UIObjectBase.hpp"

class UIObject : public UiObjectBase {

public:
    char* _editText = new char[128];

    std::string enteredText = "";

    bool _objectReplaceMode = false;

    virtual void draw() override;
    virtual void drawObjectContents() override;

    static const int oObjectChanged = 10;
    static const int oAutocomplete = 20;

    void clearEditText()
    {
        _editText[0] = '\0';
    }

    void finishedEditingText();

    //    static const int oSelected = 30;

    virtual void onMouseDoubleClick(ImVec2 pos) override

    {
        //                assert(windowController());
        windowController()->isEditingText = true;

        windowController()->restoreContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ClearInputCharacters();
        io.MouseDoubleClicked[0] = false;

        _objectReplaceMode = true;
    };
};

#endif /* NodeObject_hpp */
