#ifndef UI_MATRIX_H
#define UI_MATRIX_H

#include "baseUIClass.h"

using namespace ceammc;

class UIpdMatrix : public BaseUIObject
{
private:
    float _value;

public:
   UIpdMatrix(const PdArgs& a);
   void onBang();
   void onAny(t_symbol *, const AtomList &);
   void onFloat(float);

   float value();

   void updateUI();

};
#endif // UI_BANG_H
