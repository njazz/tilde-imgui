#ifndef PD_CATCHER_H
#define PD_CATCHER_H

#include "cpd/cpd_types.h"

#include "pd_object.h"

namespace xpd {

class PdCatcher : public PdObject {
    mutable t_cpd_object* obj_;

public:
    PdCatcher(Canvas* cnv);
    ~PdCatcher();
    bool isEmpty() const;
    bool isLastBang() const;
    bool isLastFloat(float v) const;

    void clear();
};
}

#endif // PD_CATCHER_H
