#ifndef BASE_UI_CLASS
#define BASE_UI_CLASS

#include "m_pd.h"
#include <ceammc_object.h>

#include "tilde~_ui_library/tilde~_ui_library.h"

using namespace ceammc;

namespace ceammc {
class BaseUIObject : public BaseObject {

protected:
    void forwardUIMessage(long ptr, AtomList list);
public:
    BaseUIObject(const PdArgs& a);

    virtual void updateUI();
};
}

#endif
