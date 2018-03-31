#ifndef UI_SLIDERS_H
#define UI_SLIDERS_H

#include "baseUIClass.h"

using namespace ceammc;

class UIpdSliders : public BaseUIObject
{
private:
    float _value;

public:
   UIpdSliders(const PdArgs& a);
   void onBang();
   void onAny(t_symbol *, const AtomList &);
   void onFloat(float);

   float value();

   void updateUI();
};
#endif // UI_BANG_H
