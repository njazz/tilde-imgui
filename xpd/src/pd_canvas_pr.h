#ifndef PD_CANVAS_PR_H
#define PD_CANVAS_PR_H

// this is private header only for pd_canvas.cpp and testing purposes
#include <string>

#include "cpd/cpd_types.h"
#include "xlets.h"

namespace {

static bool isSubpatchName(const std::string& name)
{
    if (name == "pd" || name.substr(0, 3) == "pd ")
        return true;
    else
        return false;
}

static xpd::XletType inletTypeToXpd(t_cpd_conn_type t)
{
    switch (t) {
    case CPD_CONNECTION_CONTROL:
        return xpd::XLET_MESSAGE;
    case CPD_CONNECTION_SIGNAL:
        return xpd::XLET_SIGNAL;
    }
}
}

#endif // PD_CANVAS_PR_H
