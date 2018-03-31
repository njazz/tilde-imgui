#include "cpd_loader.h"
#include "pr_log.h"

extern "C" {
#include "m_pd.h"
#include "s_stuff.h"
}

int cpd_load_library(t_cpd_symbol* s)
{
    return sys_load_lib(canvas_getcurrent(), s->s_name);
}
