//
//  oopdclass.cpp
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

static t_class* oopdclass_class;

typedef struct _oopdclass {
    t_object x_obj;

    t_updateUI updateUI;
    void* uiobj;

    t_outlet* out1;

} t_oopdclass;

// special
//extern "C" void oopdclass_set_updateUI(t_pd* x, void* obj, t_updateUI func)
//{
//    //weird fix, test that
//    if (x) {
//        ((t_oopdclass*)x)->updateUI = func;
//        ((t_oopdclass*)x)->uiobj = obj;
//    }
//}

static void oopdclass_anything(t_oopdclass* x, t_symbol* s, int argc, t_atom* argv)
{
    if (s == gensym("__output")) {
        AtomList l = AtomList(argc, argv);
        l.output(x->out1);
    } else {

        if (x->updateUI)
        {
            AtomList out = AtomList(s);
            out.append(AtomList(argc, argv));

            x->updateUI (x->uiobj, out);
        }

    }
}

static void* oopdclass_new(t_symbol* s, int argc, t_atom* argv)
{
    t_oopdclass* x = (t_oopdclass*)pd_new(oopdclass_class);

    x->out1 = outlet_new((t_object*)x, &s_anything);

    x->uiobj = 0;

    return (void*)x;
}

static void oopdclass_free(t_object* obj)
{
    // stub. free method is possibly useless here
    t_oopdclass* x = (t_oopdclass*)obj;
}

//extern "C"
extern "C" void setup_pdclass()
{
    oopdclass_class = class_new(gensym("pdclass"),
        (t_newmethod)(oopdclass_new),
        (t_method)(0),
        sizeof(t_oopdclass), 0, A_GIMME, 0);

    class_addmethod(oopdclass_class, (t_method)oopdclass_anything, &s_anything, A_GIMME, 0);
}
