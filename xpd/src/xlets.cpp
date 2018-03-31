#include "xlets.h"

namespace xpd {

Xlet::Xlet(XletType t)
    : type_(t)
{
}

XletType Xlet::type() const
{
    return type_;
}

Inlet::Inlet(XletType t)
    : Xlet(t)
{
}

Outlet::Outlet(XletType t)
    : Xlet(t)
{
}

} // namespace xpd
