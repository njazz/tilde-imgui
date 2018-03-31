//
//  oopdproperty.cpp
//
//
//  Created by Alex Nadzharov on 24/03/17.
//
//

#include "m_pd.h"

#include "pdlib.hpp"

#include "../ceammc-lib/ceammc_atomlist.h"
#include <stdlib.h>

using namespace ceammc;

static t_class* oopdproperty_class;

typedef struct _oopdproperty {
    t_object x_obj;

    t_updateUI updateUI;
    void* uiobj;

    t_outlet* out1;
    t_outlet* out2;
    t_outlet* out3;

} t_oopdproperty;

// special
//extern "C" void oopdproperty_set_updateUI(t_pd* x, void* obj, t_updateUI func)
//{
//    //weird fix, test that
//    if (x) {
//        ((t_oopdproperty*)x)->updateUI = func;
//        ((t_oopdproperty*)x)->uiobj = obj;
//    }
//}

static void oopdproperty_anything(t_oopdproperty* x, t_symbol* s, int argc, t_atom* argv)
{
    if (s == gensym("__output")) {
        AtomList l = AtomList(argc, argv);
        l.output(x->out1);
    } else {

        if (x->updateUI) {
            AtomList out = AtomList(s);
            out.append(AtomList(argc, argv));

            x->updateUI(x->uiobj, out);
        }
    }
}

static void* oopdproperty_new(t_symbol* s, int argc, t_atom* argv)
{
    t_oopdproperty* x = (t_oopdproperty*)pd_new(oopdproperty_class);

    x->out1 = outlet_new((t_object*)x, &s_anything);
    x->out2 = outlet_new((t_object*)x, &s_anything);
    x->out3 = outlet_new((t_object*)x, &s_anything);

    x->uiobj = 0;

    return (void*)x;
}

static void oopdproperty_free(t_object* obj)
{
    // stub. free method is possibly useless here
    t_oopdproperty* x = (t_oopdproperty*)obj;
}

//extern "C"
extern "C" void setup_pdproperty()
{
    oopdproperty_class = class_new(gensym("pdproperty"),
        (t_newmethod)(oopdproperty_new),
        (t_method)(0),
        sizeof(t_oopdproperty), 0, A_GIMME, 0);

    class_addmethod(oopdproperty_class, (t_method)oopdproperty_anything, &s_anything, A_GIMME, 0);
}
