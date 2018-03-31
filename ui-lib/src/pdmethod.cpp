//
//  oopdmethod.cpp
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

static t_class* oopdmethod_class;

typedef struct _oopdmethod {
    t_object x_obj;

    t_updateUI updateUI;
    void* uiobj;

    t_outlet* out1;

} t_oopdmethod;

// special
//extern "C" void oopdmethod_set_updateUI(t_pd* x, void* obj, t_updateUI func)
//{
//    //weird fix, test that
//    if (x) {
//        ((t_oopdmethod*)x)->updateUI = func;
//        ((t_oopdmethod*)x)->uiobj = obj;
//    }
//}

static void oopdmethod_anything(t_oopdmethod* x, t_symbol* s, int argc, t_atom* argv)
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

static void* oopdmethod_new(t_symbol* s, int argc, t_atom* argv)
{
    t_oopdmethod* x = (t_oopdmethod*)pd_new(oopdmethod_class);

    x->out1 = outlet_new((t_object*)x, &s_anything);

    x->uiobj = 0;

    return (void*)x;
}

static void oopdmethod_free(t_object* obj)
{
    // stub. free method is possibly useless here
    t_oopdmethod* x = (t_oopdmethod*)obj;
}

//extern "C"
extern "C" void setup_pdmethod()
{
    oopdmethod_class = class_new(gensym("pdmethod"),
        (t_newmethod)(oopdmethod_new),
        (t_method)(0),
        sizeof(t_oopdmethod), 0, A_GIMME, 0);

    class_addmethod(oopdmethod_class, (t_method)oopdmethod_anything, &s_anything, A_GIMME, 0);
}
