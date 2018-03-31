#include "cpd_canvas.h"
#include "cpd_list.h"
#include "cpd_object.h"
#include "pr_log.h"

#include "m_pd.h"
extern "C" {
#include "g_canvas.h"
#include "m_imp.h"
#include "s_stuff.h"
}

#define NULL_CHECK(obj)         \
    if (obj == nullptr) {       \
        DEBUG("NULL argument"); \
        return;                 \
    }

#define NULL_CHECK_RETURN(obj, ret) \
    if (obj == nullptr) {           \
        DEBUG("NULL argument");     \
        return ret;                 \
    }

const char* cpd_canvas_name(t_cpd_canvas* cnv)
{
    NULL_CHECK_RETURN(cnv, nullptr);

    return cnv->gl_name->s_name;
}

int cpd_canvas_free(t_cpd_canvas* cnv)
{
    NULL_CHECK_RETURN(cnv, 0);

    canvas_free(cnv);
    return 1;
}

t_cpd_canvas* cpd_canvas_root(t_cpd_canvas* cnv)
{
    NULL_CHECK_RETURN(cnv, nullptr);

    return canvas_getrootfor(cnv);
}

int cpd_canvas_fontsize(t_cpd_canvas* cnv)
{
    NULL_CHECK_RETURN(cnv, -1);

    return cnv->gl_font;
}

int cpd_canvas_is_root(t_cpd_canvas* cnv)
{
    NULL_CHECK_RETURN(cnv, 0);

    return cnv->gl_owner == 0 ? 1 : 0;
}

t_cpd_canvas* cpd_canvas_current()
{
    return canvas_getcurrent();
}

size_t cpd_canvas_object_count(t_cpd_canvas* cnv)
{
    NULL_CHECK_RETURN(cnv, 0);

    t_gobj* l = cnv->gl_list;
    size_t n = 0;

    while (l) {
        if (l->g_pd->c_patchable)
            n++;

        l = l->g_next;
    }

    return n;
}

t_cpd_object* cpd_canvas_first_object(t_cpd_canvas* cnv)
{
    NULL_CHECK_RETURN(cnv, nullptr);

    t_gobj* l = cnv->gl_list;
    while (l) {
        if (l->g_pd->c_patchable)
            return reinterpret_cast<t_cpd_object*>(l);

        l = l->g_next;
    }

    return nullptr;
}

void cpd_canvas_set_current(t_cpd_canvas* cnv)
{
    NULL_CHECK(cnv);

    canvas_setcurrent(cnv);
}

void cpd_canvas_unset_current(t_cpd_canvas* cnv)
{
    NULL_CHECK(cnv);

    canvas_unsetcurrent(cnv);
}

t_cpd_object* cpd_canvas_to_object(t_cpd_canvas* cnv)
{
    NULL_CHECK_RETURN(cnv, nullptr);

    return &cnv->gl_obj;
}

t_cpd_object* cpd_canvas_object_at(t_cpd_canvas* cnv, size_t n)
{
    NULL_CHECK_RETURN(cnv, nullptr);

    t_gobj* l = cnv->gl_list;
    size_t cur = 0;
    while (l) {
        if (l->g_pd->c_patchable) {
            if (n == cur)
                return reinterpret_cast<t_cpd_object*>(l);

            cur++;
        }

        l = l->g_next;
    }

    return nullptr;
}

void cpd_canvas_loadbang(t_cpd_canvas* cnv)
{
    NULL_CHECK(cnv);

    canvas_loadbang(cnv);
}


