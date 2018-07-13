//
//  NodeObject.hpp
//  nseq
//
//  Created by Alex on 23/03/2018.
//  Copyright © 2018 Alex Nadzharov. All rights reserved.
//

#ifndef UIPropertiesWindow_hpp
#define UIPropertiesWindow_hpp

#include "IUView.hpp"
#include "PropertyList.h"

class UIPropertiesWindow : public IULayer {
    PropertyList* _properties = 0;
    bool* _display = 0;

public:
    UIPropertiesWindow(PropertyList* p, bool* d);

    virtual void _drawContents() override;
};

#endif /* NodeObject_hpp */
