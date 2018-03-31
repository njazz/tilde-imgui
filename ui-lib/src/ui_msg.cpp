//
//  ui_msg.cpp
//
//
//  Created by Alex Nadzharov on 03/03/17.
//
//

#include <ceammc_factory.h>
#include "m_pd.h"
#include "ui_msg.h"

using namespace ceammc;

class UIpdMsg;

void UIpdMsg::updateUI()
{
    forwardUIMessage((long)owner(), getMessage());
}

UIpdMsg::UIpdMsg(const PdArgs& a)
    : BaseUIObject(a)
{
    createOutlet();
}

void UIpdMsg::_setMessage(AtomList list)
{
    _message.clear();
    if (list.size() != 0) {
        _message = list;
        updateUI();
    }
}

void UIpdMsg::_processDollars(AtomList* list)
{
    for (size_t i = 0; i < list->size(); i++) {
        if (AtomList(list->at(i)).toPdData()->a_type == A_DOLLAR) {

            //post("dollar args");
            size_t idx = AtomList(list->at(i)).toPdData()->a_w.w_index - 1;

            if ((idx < _inputList.size()) && (idx >= 0)) {
                list->at(i) = _inputList.at(idx);
            } else {
                list->at(i) = Atom(0.f);
                post("argument index out of range");
            }
        }
    }
}

void UIpdMsg::_doOutput()
{
    if (_message.size()) {

        int start = 0;
        int end = 0;

        for (size_t i = 0; i < _message.size(); i++) {
            if ((AtomList(_message.at(i)).toPdData()->a_type == A_COMMA)
                || (i == (_message.size() - 1))) {
                end = i + (i == (_message.size() - 1));

                if ((_message.at(start).asSymbol() == gensym(";")) || (AtomList(_message.at(start)).toPdData()->a_type == A_SEMI)) {

                    start += 1;
                    if (!_message.at(start).isSymbol()) {
                        error("ui.msg: bad destination!");

                    } else {
                        t_symbol* sym = _message.at(start).asSymbol();
                        start += 1;

                        if (sym->s_thing) {

                            AtomList l1 = _message.slice(start, end);
                            _processDollars(&l1);

                            //t_object* obj = pd_checkobject(sym->s_thing);
                            t_object* obj = (t_object*)sym->s_thing;
                            if (obj) {
                                pd_forwardmess((t_pd*)obj, l1.size(), l1.toPdData());
                            } else {
                                error("ui.msg: bad destination object for symbol: %s", sym->s_name);
                            }

                        } else {
                            error("ui.msg: destination not found!");
                        }
                    }

                } else {
                    AtomList l1 = _message.slice(start, end);
                    _processDollars(&l1);

                    if (l1[0].isSymbol()) {

                        AtomList outList = l1;
                        outList.remove(0);
                        anyTo(0, l1[0].asSymbol(), outList);

                    } else {
                        listTo(0, l1);
                    }
                }

                start = i + 1;
            }
        }
    }
}

void UIpdMsg::onBang()
{
    _inputList.clear();
    _doOutput();
}

void UIpdMsg::onAny(t_symbol* s, const AtomList& list0)
{
    AtomList list = list0;

    list.insert(0, AtomList(s));

    if (s == gensym("set")) {
        _setMessage(list0);
    } else {
        //variables

        _inputList.clear();
        _inputList = list0;
        _doOutput();
    }
}

void UIpdMsg::onList(const AtomList& list)
{
    UIpdMsg::onAny(gensym("list"), list);
}

void UIpdMsg::onFloat(float f)
{
    UIpdMsg::onAny(gensym("float"), AtomList(Atom(f)));
}

AtomList UIpdMsg::getMessage() { return _message; };

extern "C" void setup_ui0x2emsg()
{
    ObjectFactory<UIpdMsg> obj("ui.msg");
}
