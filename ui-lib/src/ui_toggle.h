#ifndef UI_TOGGLE
#define UI_TOGGLE

#include "baseUIClass.h"

using namespace ceammc;

class UIpdToggle : public BaseUIObject
{
private:
    float _value;

public:
   UIpdToggle(const PdArgs& a);
   void onBang();
   //void onAny(t_symbol *, const AtomList &);
   void onFloat(float);

   float value(){return _value;}

   void updateUI();
};
#endif // UI_BANG_H
