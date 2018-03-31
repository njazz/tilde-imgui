#ifndef UI_FLOAT_H
#define UI_FLOAT_H

#include "baseUIClass.h"

using namespace ceammc;

class UIpdFloat : public BaseUIObject
{
private:
    float _value;

public:
   UIpdFloat(const PdArgs& a);
   void onBang();
   void onAny(t_symbol *s, const AtomList &);
   void onFloat(float f);

   float value();

   void updateUI();
};

#endif // UI_BANG_H
