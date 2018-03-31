//
//  ui_float.cpp
//
//
//  Created by Alex Nadzharov on 13/03/17.
//
//

#include <ceammc_factory.h>
#include "ui_float.h"

using namespace ceammc;

class UIpdFloat;

void UIpdFloat::updateUI()
{
    forwardUIMessage((long)owner(), AtomList(Atom(value())));
}

float UIpdFloat::value()
{
    return _value;
}

UIpdFloat::UIpdFloat(const PdArgs& a)
    : BaseUIObject(a)
{
    _value = 0;
    createOutlet();
}

void UIpdFloat::onBang()
{
    floatTo(0, _value);
    updateUI();
}

void UIpdFloat::onFloat(float f)
{
    _value = f;
    UIpdFloat::onBang();
}

void UIpdFloat::onAny(t_symbol* s, const AtomList& list)
{
    if (s == gensym("set") && list.size() > 0) {
        _value = list.at(0).asFloat();
    }
}
extern "C" void setup_ui0x2efloat()
{
    ObjectFactory<UIpdFloat> obj("ui.float");
}
