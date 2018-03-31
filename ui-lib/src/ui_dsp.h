#ifndef UI_BANG_H
#define UI_BANG_H

#include "baseUIClass.h"

using namespace ceammc;

class UIpdDSP : public BaseUIObject
{
    bool _value;
public:
   UIpdDSP(const PdArgs& a);
   void onAny(t_symbol *, const AtomList &);

   virtual void updateUI();

};

#endif // UI_BANG_H
