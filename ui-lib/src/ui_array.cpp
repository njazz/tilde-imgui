//  ui_bang.cpp
//
//
//  Created by Alex Nadzharov on 03/03/17.
//

#include <ceammc_factory.h>
#include "ui_array.h"

using namespace ceammc;

class UIpdArray;
static void qtpd_update(UIpdArray* x)
{
    // XPD-TODO
    //forwardUIMessage((long)x, AtomList(Atom(gensym("bang"))));
}

UIpdArray::UIpdArray(const PdArgs& a)
    : BaseUIObject(a)
{
}

extern "C" void setup_ui0x2earray()
{
    ObjectFactory<UIpdArray> obj("ui.array");
}
