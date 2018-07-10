//
//  NodeInlet.hpp
//  nseq
//
//  Created by Alex on 23/03/2018.
//  Copyright © 2018 Alex Nadzharov. All rights reserved.
//

#ifndef Grid_hpp
#define Grid_hpp

#include "IUView.hpp"
#include <stdio.h>

#include "imgui_internal.h"

class Grid : public IULayer {

public:
    bool *editModeFlag = 0;
    bool *showGrid = 0;
    int *gridStep = 0;

    virtual void drawLayerContents() override;

    Grid(){manualLayout = true;}
};

#endif /* NodeInlet_hpp */
