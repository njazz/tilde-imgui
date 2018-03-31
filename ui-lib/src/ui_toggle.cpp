//
//  ui_toggle.cpp
//
//  Created by Alex Nadzharov on 03/03/17.

#include "ui_toggle.h"
#include <ceammc_factory.h>

using namespace ceammc;

class UIpdToggle;

void UIpdToggle::updateUI()
{
    forwardUIMessage((long)owner(), AtomList(Atom(_value)));
}

UIpdToggle::UIpdToggle(const PdArgs& a)
    : BaseUIObject(a)
{
    _value = 0;
    createOutlet();
}

void UIpdToggle::onBang()
{
    _value = float(!(_value > 0));
    floatTo(0, _value);
    updateUI();
}

void UIpdToggle::onFloat(float f)
{
    _value = f;
    floatTo(0, _value);

    updateUI();
}

extern "C" void setup_ui0x2etoggle()
{
    ObjectFactory<UIpdToggle> obj("ui.toggle");
}

