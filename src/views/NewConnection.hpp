//
//  NodeInlet.hpp
//  nseq
//
//  Created by Alex on 23/03/2018.
//  Copyright © 2018 Alex Nadzharov. All rights reserved.
//

#ifndef NewConnection_hpp
#define NewConnection_hpp

#include <stdio.h>
#include "IUView.hpp"

class ObjectBase;

class NewConnection:public IUView
{
    
public:
    ObjectBase* outputObj = 0;
    int outputIdx;

    ObjectBase* inputObj = 0;
    int inputIdx;
    float inputX;
    float inputY;
    
    virtual void draw();
    
};

#endif /* NodeInlet_hpp */
