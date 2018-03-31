//
//  ui_sliders.cpp
//
//
//  Created by Alex Nadzharov on 13/03/17.
//
//

#include <ceammc_factory.h>
#include <stdlib.h>
#include "ui_sliders.h"

using namespace ceammc;

class UIpdSliders;

void UIpdSliders::updateUI()
{
    forwardUIMessage((long)owner(), AtomList(Atom(value())));
}

float UIpdSliders::value()
{
    return _value;
}

UIpdSliders::UIpdSliders(const PdArgs& a)
    : BaseUIObject(a)
{
    _value = 0;
    createOutlet();
}

void UIpdSliders::onBang()
{
    floatTo(0, _value);
    updateUI();
}

void UIpdSliders::onFloat(float f)
{
    _value = f;
    UIpdSliders::onBang();
}

void UIpdSliders::onAny(t_symbol* s, const AtomList& list)
{
    if (s == gensym("set") && list.size() > 0) {
        _value = list.at(0).asFloat();
    }
}

extern "C" void setup_ui0x2esliders()
{
    ObjectFactory<UIpdSliders> obj("ui.slider");
}
