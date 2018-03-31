//
//  ui_matrix.cpp
//
//
//  Created by Alex Nadzharov on 29/04/17.
//
//

#include <ceammc_factory.h>
#include <stdlib.h>
#include "math.h"
#include "ui_matrix.h"

using namespace ceammc;

class UIpdMatrix;

void UIpdMatrix::updateUI()
{
    forwardUIMessage((long)owner(), AtomList(Atom(value())));
}

float UIpdMatrix::value()
{
    return _value;
}

UIpdMatrix::UIpdMatrix(const PdArgs& a)
    : BaseUIObject(a)
{
    _value = 0;
    createOutlet();
}

void UIpdMatrix::onBang()
{
    floatTo(0, _value);
    updateUI();
}

void UIpdMatrix::onFloat(float f)
{
    _value = floor(f);
    UIpdMatrix::onBang();
}

void UIpdMatrix::onAny(t_symbol* s, const AtomList& list)
{
    if (s == gensym("set") && list.size() > 0) {
        _value = list.at(0).asFloat();
    }
}
extern "C" void setup_ui0x2ematrix()
{
    ObjectFactory<UIpdMatrix> obj("ui.matrix");
    obj.addAlias("ui.radio");
    //ObjectFactory<UIpdMatrix> obj2("ui.radio");
}

//static t_class* ui_matrix_class;

//typedef struct _ui_matrix {
//    t_object x_obj;

//    t_updateUI updateUI;
//    void* uiobj;

//    float val;

//    t_outlet* out1;

//} t_ui_matrix;

//// special
//extern "C" void uimatrix_set_updateUI(t_pd* x, void* obj, t_updateUI func)
//{
//    ((t_ui_matrix*)x)->updateUI = func;
//    ((t_ui_matrix*)x)->uiobj = obj;
//}

/////////

//static void uimatrix_set(t_ui_matrix* x, t_symbol* s, int argc, t_atom* argv)
//{
//    if (argc)
//        x->val = floor(AtomList(argc, argv).at(0).asFloat());

//    //cautionary
//    AtomList msg = AtomList(Atom(floor(x->val)));

//    if (x->updateUI)
//        x->updateUI(x->uiobj, msg);
//}

//static void uimatrix_bang(t_ui_matrix* x)
//{
//    AtomList(Atom(x->val)).output(x->out1);
//}

//static void uimatrix_float(t_ui_matrix* x, t_float f)
//{
//    x->val = floor(f);

//    AtomList msg = AtomList(Atom(x->val));

//    msg.output(x->out1);

//    if (x->updateUI)
//        x->updateUI(x->uiobj, msg);
//}

/////////

//static void* uimatrix_new(t_symbol* s, int argc, t_atom* argv)
//{
//    t_ui_matrix* x = (t_ui_matrix*)pd_new(ui_matrix_class);

//    x->val = 0;

//    x->out1 = outlet_new((t_object*)x, &s_anything);

//    x->uiobj = 0;

//    return (void*)x;
//}

//static void uimatrix_free(t_object* obj)
//{
//}

////extern "C"
//extern "C" void setup_ui0x2ematrix()
//{
//    ui_matrix_class = class_new(gensym("ui.matrix"),
//        (t_newmethod)(uimatrix_new),
//        (t_method)(0),
//        sizeof(t_ui_matrix), 0, A_GIMME, 0);

//    class_addmethod(ui_matrix_class, (t_method)uimatrix_set, &s_anything, A_GIMME, 0);
//    class_addmethod(ui_matrix_class, (t_method)uimatrix_bang, &s_bang, A_NULL, 0);

//    class_addfloat(ui_matrix_class, (t_method)uimatrix_float);
//}
