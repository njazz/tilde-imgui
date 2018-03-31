#include "cpd_patch.h"
#include "cpd_canvas.h"
#include "cpd_list.h"
#include "cpd_object.h"
#include "pr_log.h"
#include "spdlog/spdlog.h"

#include "m_pd.h"
extern "C" {
#include "g_canvas.h"
#include "m_imp.h"
#include "s_stuff.h"
}

#define NULL_CHECK_RETURN(obj, ret) \
    if (obj == nullptr) {           \
        DEBUG("NULL argument");     \
        return ret;                 \
    }

t_cpd_canvas* cpd_patch_new()
{
    static int cnt = 1;
    fmt::MemoryWriter w;
    w.write("Untitled-{}", cnt++);

    if (canvas_getcurrent())
        canvas_unsetcurrent(canvas_getcurrent());

    glob_setfilename(0, gensym(w.c_str()), gensym("~/"));
    t_cpd_canvas* res = canvas_new(0, 0, 0, 0);
    return res;
}

t_cpd_canvas* cpd_patch_load(const char* name, const char* path)
{
    if (name && path) {
        t_cpd_canvas* cnv = reinterpret_cast<t_cpd_canvas*>(glob_evalfile(NULL, gensym(name), gensym(path)));

        if (cnv) {
            DEBUG("loaded \"{}/{}\"", path, name);
            return cnv;
        }

        return nullptr;
    }

    if (name) {
        t_namelist* dir_entry = STUFF->st_searchpath;

        while (dir_entry) {
            const char* rpath = dir_entry->nl_string;

            t_cpd_canvas* cnv = reinterpret_cast<t_cpd_canvas*>(glob_evalfile(NULL, gensym(name), gensym(rpath)));
            if (cnv) {
                DEBUG("loaded \"{}/{}\"", rpath, name);
                return cnv;
            }

            dir_entry = dir_entry->nl_next;
        }
    }

    return nullptr;
}

t_cpd_canvas* cpd_patchlist_last()
{
    t_cpd_canvas* cnv = pd_getcanvaslist();

    if (!cnv)
        return cnv;

    while (cnv->gl_next) {
        cnv = cnv->gl_next;
    }

    return cnv;
}

size_t cpd_patchlist_count()
{
    t_cpd_canvas* cnv = pd_getcanvaslist();

    size_t n = 0;

    while (cnv) {
        cnv = cnv->gl_next;
        n++;
    }

    return n;
}

t_cpd_canvas* cpd_patchlist_at(size_t n)
{
    t_cpd_canvas* cnv = pd_getcanvaslist();

    size_t cur = 0;

    while (cnv) {
        if (cur == n)
            return cnv;

        cnv = cnv->gl_next;
        cur++;
    }

    return 0;
}

t_cpd_canvas* cpd_patchlist_next(t_cpd_canvas* cnv)
{
    NULL_CHECK_RETURN(cnv, nullptr);

    return cnv->gl_next;
}

const char* cpd_patch_dir(t_cpd_canvas* cnv)
{
    NULL_CHECK_RETURN(cnv, "");

    if (cpd_canvas_is_root(cnv) && canvas_getenv(cnv))
        return canvas_getdir(cnv)->s_name;

    DEBUG("non root canvas given");
    return "";
}

int cpd_patch_xpos(t_cpd_canvas* cnv)
{
    NULL_CHECK_RETURN(cnv, 0);

    return cnv->gl_screenx1;
}

int cpd_patch_ypos(t_cpd_canvas* cnv)
{
    NULL_CHECK_RETURN(cnv, 0);

    return cnv->gl_screeny1;
}

int cpd_patch_width(t_cpd_canvas* cnv)
{
    NULL_CHECK_RETURN(cnv, 0);

    return cnv->gl_screenx2 - cnv->gl_screenx1;
}

int cpd_patch_height(t_cpd_canvas* cnv)
{
    NULL_CHECK_RETURN(cnv, 0);

    return cnv->gl_screeny2 - cnv->gl_screeny1;
}

t_cpd_canvas* cpd_subpatch_new(t_cpd_canvas* parent, const char* name, t_cpd_list* args, int x, int y)
{
    NULL_CHECK_RETURN(parent, nullptr);

    bool free_arg_list = false;
    t_cpd_list* subpatch_args = 0;

    if (args) {
        // put name first
        subpatch_args = args;
        cpd_list_prepend_symbol(subpatch_args, cpd_symbol(name));
    } else {
        free_arg_list = true;
        subpatch_args = cpd_list_new(0);
        cpd_list_append_symbol(subpatch_args, cpd_symbol(name));
    }

    t_cpd_object* sub = cpd_object_new(parent, "pd", subpatch_args, x, y);
    if (!sub) {
        DEBUG("can't create subpatch");
        return nullptr;
    }

    if (free_arg_list)
        cpd_list_free(subpatch_args);

    return reinterpret_cast<t_cpd_canvas*>(sub);
}

int cpd_patch_save(t_cpd_canvas* patch, const char* name, const char* dir)
{
    NULL_CHECK_RETURN(patch, 0);

    if (!name || !dir) {
        DEBUG("name and dir required");
        return 0;
    }

    t_cpd_list* args = cpd_list_new(0);
    cpd_list_append_symbol(args, cpd_symbol(name));
    cpd_list_append_symbol(args, cpd_symbol(dir));

    pd_typedmess(&patch->gl_obj.te_g.g_pd, gensym("savetofile"), cpd_list_size(args), cpd_list_at(args, 0));
    cpd_list_free(args);
    return 1;
}
