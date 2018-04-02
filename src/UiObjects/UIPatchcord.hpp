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

class ObjectBase;

class UIPatchcord : public IUView {

public:
    ObjectBase* outputObj;
    int outputIdx;
    ObjectBase* inputObj;
    int inputIdx;

    virtual void draw();

    bool selected;

};

#endif /* NodeInlet_hpp */

