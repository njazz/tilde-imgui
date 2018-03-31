//
//  ui_bang.cpp
//
//
//  Created by Alex Nadzharov on 03/03/17.
//

#include "ui_dsp.h"
#include "ceammc_atomlist.h"
#include "ceammc_factory.h"
#include "m_pd.h"

using namespace ceammc;

class UIpdDSP;

void UIpdDSP::updateUI()
{
    forwardUIMessage((long)owner(), AtomList(Atom(_value)));
}

UIpdDSP::UIpdDSP(const PdArgs& a)
    : BaseUIObject(a)
{
    createOutlet();

    pd_bind((t_pd*)owner(), gensym("pd"));
}

void UIpdDSP::onAny(t_symbol* s, const AtomList& l)
{
    //post("sym %s",s);
    if (s == gensym("dsp"))
        if (l.size() > 0) {
            _value = l.at(0).asFloat() > 0;
            updateUI();
        }
}

extern "C" void setup_ui0x2edsp()
{
    ObjectFactory<UIpdDSP> obj("ui.dsp");
}
