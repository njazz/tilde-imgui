#ifndef UI_MSG_H
#define UI_MSG_H

#include "baseUIClass.h"

using namespace ceammc;

class UIpdMsg : public BaseUIObject {
private:
    AtomList _inputList;
    AtomList _message;

    void _doOutput();
    void _setMessage(AtomList list);
    void _processDollars(AtomList* list);

public:
    UIpdMsg(const PdArgs& a);
    void onBang();
    void onAny(t_symbol* s, const AtomList& list);
    void onList(const AtomList& list);
    void onFloat(float f);

    AtomList getMessage();

    void updateUI();
};

#endif // UI_BANG_H
