#ifndef UI_BANG_H
#define UI_BANG_H

#include "baseUIClass.h"

using namespace ceammc;

class UIpdBang : public BaseUIObject
{
public:
   UIpdBang(const PdArgs& a);
   void onBang();
   void onAny(t_symbol *, const AtomList &);
   void onFloat(float);

   virtual void updateUI();

};

#endif // UI_BANG_H
