#include "baseUIClass.h"
#include <sstream>

BaseUIObject::BaseUIObject(const PdArgs& a)
    : BaseObject(a)
{
}

void BaseUIObject::updateUI()
{
    forwardUIMessage(AtomList());
}

void BaseUIObject::forwardUIMessage(AtomList list)
{
    //printf("forward msg");

    long ptr = reinterpret_cast<long>(owner());

    list.insert(0, Atom(gensym(std::to_string(ptr).c_str())));

    t_symbol* receiver = gensym("xpd_receiver");

    if (receiver->s_thing)
        pd_typedmess(receiver->s_thing, gensym("ui_object"), list.size(), list.toPdData());
    else
    {
        error("xpd_receiver symbol error!");
        printf("xpd_receiver symbol error!\n");

    }
}
