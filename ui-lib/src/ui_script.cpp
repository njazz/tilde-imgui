//
//  ui_script.cpp
//
//
//  Created by Alex Nadzharov on 24/03/17.
//
//

#include <ceammc_factory.h>
#include <stdlib.h>
#include "ui_script.h"

using namespace ceammc;

UIpdScript::UIpdScript(const PdArgs& a)
    : BaseUIObject(a)
{
    createOutlet();
}
void UIpdScript::onBang()
{
    // XPD-TODO
    // UIUpdate((long)this->owner(), AtomList());
}

void UIpdScript::onFloat(float f)
{
    // XPD-TODO
    // UIUpdate((long)this->owner(), AtomList(Atom(f)));
}

void UIpdScript::onAny(t_symbol* s, const AtomList& list)
{
    if (s == gensym("-py-output") && list.size() > 0) {
        //TODO
        anyTo(0, gensym("list"), list);
    } else {
        onBang();
    }
}
extern "C" void setup_ui0x2escript()
{
    ObjectFactory<UIpdScript> obj("ui.script");

    obj.addAlias("py");
}
