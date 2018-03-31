#include "pd_catcher.h"
#include "cpd/cpd_catcher.h"
#include "pd_canvas.h"

using namespace xpd;

static bool init_ = false;

Canvas* wrap(Canvas* c)
{
    if (!init_) {
        cpd_catcher_init();
    }

    return c;
}

PdCatcher::PdCatcher(Canvas* cnv)
    : PdObject(wrap(cnv), "@catcher object@")
{
    PdCanvas* pd_cnv = dynamic_cast<PdCanvas*>(cnv);
    pd_cnv->obj_list_.append(this);

    obj_ = pd_cnv->findById(id());
}

PdCatcher::~PdCatcher()
{
    PdCanvas* pd_cnv = (PdCanvas*)(parent());
    if (!pd_cnv)
        return;

    auto idx = pd_cnv->obj_list_.findObjectIndex(id());
    if (idx < 1)
        return;

    pd_cnv->obj_list_.removeIndex(idx);
}

bool PdCatcher::isEmpty() const
{
    return cpd_catcher_empty(obj_);
}

bool PdCatcher::isLastBang() const
{
    return cpd_catcher_last_bang(obj_);
}

bool PdCatcher::isLastFloat(float v) const
{
    return cpd_catcher_last_float(obj_, v);
}

void PdCatcher::clear()
{
    cpd_catcher_clear(obj_);
}
