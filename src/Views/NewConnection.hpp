//
//  NodeInlet.hpp
//  nseq
//
//  Created by Alex on 23/03/2018.
//  Copyright © 2018 Alex Nadzharov. All rights reserved.
//

#ifndef NewConnection_hpp
#define NewConnection_hpp

#include "IUView.hpp"
#include <stdio.h>

class UiObjectBase;

class NewConnection : public IUView {

public:
    UiObjectBase* outputObj = 0;
    int outputIdx = 0;

    UiObjectBase* inputObj = 0;
    int inputIdx = 0;
    float inputX = 0;
    float inputY = 0;

    virtual void draw();
};

#endif /* NodeInlet_hpp */
