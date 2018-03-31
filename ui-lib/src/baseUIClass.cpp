#include "baseUIClass.h"
#include <sstream>

BaseUIObject::BaseUIObject(const PdArgs& a)
    : BaseObject(a)
{
}

void BaseUIObject::updateUI()
{
}

void BaseUIObject::forwardUIMessage(long ptr, AtomList list)
{
    t_symbol* receiver = gensym("xpd_receiver");
    std::stringstream stream;
    stream << ptr;
    list.insert(0, Atom(gensym(stream.str().c_str())));

    if (receiver->s_thing)
        pd_typedmess(receiver->s_thing, gensym("pd_ui_object"), list.size(), list.toPdData());
    else
        error("xpd_receiver symbol error!");
}
