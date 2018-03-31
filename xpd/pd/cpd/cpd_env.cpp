#include "cpd_env.h"
#include "m_pd.h"

extern "C" {
#include "s_stuff.h"
}

#include <cstring>

int cpd_version_major()
{
    return PD_MAJOR_VERSION;
}

int cpd_version_minor()
{
    return PD_MINOR_VERSION;
}

int cpd_version_bugfix()
{
    return PD_BUGFIX_VERSION;
}

void cpd_searchpath_append(const char* path)
{
    if (strlen(path) == 0)
        return;

    STUFF->st_searchpath = namelist_append(STUFF->st_searchpath, path, 0);
}

size_t cpd_searchpath_num()
{
    size_t n = 0;

    auto p1 = STUFF->st_searchpath;
    while (p1) {
        n++;
        p1 = p1->nl_next;
    }

    return n;
}

const char* cpd_searchpath_at(size_t idx)
{
    return namelist_get(STUFF->st_searchpath, idx);
}

void cpd_searchpath_clear()
{
    namelist_free(STUFF->st_searchpath);
    STUFF->st_searchpath = 0;
}

void cpd_setprinthook(t_printhook h)
{
    sys_printhook = h;
}
