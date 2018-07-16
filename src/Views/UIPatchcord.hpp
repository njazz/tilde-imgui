//
//  NodeInlet.hpp
//  nseq
//
//  Created by Alex on 23/03/2018.
//  Copyright © 2018 Alex Nadzharov. All rights reserved.
//

#ifndef NodeInlet_hpp
#define NodeInlet_hpp

#include <stdio.h>

#include "IUView.hpp"

class UiObjectBase;

class UIPatchcord : public IUView {

public:
    UiObjectBase* outputObj;
    int outputIdx;
    UiObjectBase* inputObj;
    int inputIdx;

    virtual void draw() override{_drawContents();}
    virtual void _drawContents() override;

    bool selected = false;

    // todo:
    bool isHovered(ImVec2 pos){return false;};

};

#endif /* NodeInlet_hpp */

