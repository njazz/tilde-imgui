#include "cpd_object.h"
#include "cpd.h"
#include "cpd_globals.h"
#include "pr_log.h"

#include <cstring>

#include "m_pd.h"
extern "C" {
#include "g_canvas.h"
#include "m_imp.h"
#include "s_stuff.h"
}

t_cpd_object* cpd_object_new(t_cpd_canvas* c, const char* name, const t_cpd_list* args, int x, int y)
{
    TRACE("-");

    const size_t N = cpd_list_size(args);

    std::vector<t_atom> data(N + 3);
    t_atom* argv = &data.front();

    SETFLOAT(&argv[0], x);
    SETFLOAT(&argv[1], y);
    SETSYMBOL(&argv[2], gensym(name));

    if (args) {
        auto begin = cpd_list_at(const_cast<t_cpd_list*>(args), 0);
        std::copy(begin, begin + N, argv + 3);
    }

    pd_typedmess((t_pd*)c, CPD_SYMBOL_OBJ, N + 3, argv);

    t_pd* ptr = pd_newest();
    if (!ptr) {
        cpd_error("cpd_object_new: object creation failed");
        return 0;
    }

    t_object* res = pd_checkobject(ptr);
    if (!res) {
        cpd_error("cpd_object_new: invalid object");
        return 0;
    }

    DEBUG("created [{}] ({})", name, (void*)res);
    return res;
}

void cpd_object_free(t_cpd_canvas* cnv, t_cpd_object* obj)
{
    if (!cnv) {
        ERROR("NULL canvas given");
        return;
    }

    if (!obj) {
        ERROR("NULL object given");
        return;
    }

    DEBUG("[{}]", cpd_object_name(obj));

    glist_delete(cnv, &obj->te_g);
}

const char* cpd_object_name(t_cpd_object* obj)
{
    if (!obj)
        return "";

    return obj->te_g.g_pd->c_name->s_name;
}

t_cpd_list* cpd_object_arguments(t_cpd_object* obj)
{
    if (!obj) {
        ERROR("NULL pointer given");
        return 0;
    }

    t_binbuf* b = ((t_text*)(obj))->te_binbuf;
    const t_atom* atoms = binbuf_getvec(b);
    const size_t N = binbuf_getnatom(b);

    // binbuf list contains object name as first argument
    // we have to skip it
    t_cpd_list* res = cpd_list_new(N - 1);

    for (size_t i = 0; i < N - 1; i++) {
        cpd_atom_set_atom(cpd_list_at(res, i), &atoms[i + 1]);
    }

    return res;
}

const char* cpd_object_text(t_cpd_object* obj)
{
    if (!obj) {
        ERROR("NULL pointer given");
        return nullptr;
    }

    int size = 0;
    char* txt = 0;

    // txt - not null-terminated string
    binbuf_gettext(((t_text*)(obj))->te_binbuf, &txt, &size);

    char* res = (char*)malloc(size + 1);
    memcpy(res, txt, size);
    res[size] = '\0';

    t_freebytes(txt, size);

    return res;
}

int cpd_object_xpos(t_cpd_object* obj)
{
    if (!obj)
        return -1;

    return obj->te_xpix;
}

int cpd_object_ypos(t_cpd_object* obj)
{
    if (!obj)
        return -1;

    return obj->te_ypix;
}

void cpd_object_set_xpos(t_cpd_object* obj, int x)
{
    if (!obj)
        return;

    obj->te_xpix = x;
}

void cpd_object_set_ypos(t_cpd_object* obj, int y)
{
    if (!obj)
        return;

    obj->te_ypix = y;
}

size_t cpd_object_inlet_count(t_cpd_object* obj)
{
    if (!obj)
        return 0;

    return obj_ninlets(obj);
}

size_t cpd_object_outlet_count(t_cpd_object* obj)
{
    if (!obj)
        return 0;

    return obj_noutlets(obj);
}

int cpd_connect(t_cpd_object* obj1, size_t outno, t_cpd_object* obj2, size_t inno)
{
    if (!obj1 || !obj2) {
        DEBUG("NULL objects are given");
        return 0;
    }

    if (obj1 == obj2) {
        DEBUG("self-connection");
        return 0;
    }

    if (outno >= cpd_object_outlet_count(obj1)) {
        ERROR("invalid source outlet {}", outno);
        return 0;
    }

    if (inno >= cpd_object_inlet_count(obj2)) {
        ERROR("invalid destination inlet {}", inno);
        return 0;
    }

    auto conn = obj_connect(obj1, outno, obj2, inno);
    return 1;
}

int cpd_disconnect(t_cpd_object* obj1, size_t outno, t_cpd_object* obj2, size_t inno)
{
    if (!obj1 || !obj2) {
        DEBUG("NULL objects are given");
        return 0;
    }

    if (obj1 == obj2) {
        DEBUG("self-connection");
        return 0;
    }

    if (outno >= cpd_object_outlet_count(obj1)) {
        ERROR("invalid source outlet {}", outno);
        return 0;
    }

    if (inno >= cpd_object_inlet_count(obj2)) {
        ERROR("invalid destination inlet {}", inno);
        return 0;
    }

    obj_disconnect(obj1, outno, obj2, inno);
    return 1;
}

int cpd_is_canvas(t_cpd_object* x)
{
    if (!x) {
        ERROR("null pointer given");
        return 0;
    }

    return (pd_class(&x->te_pd) == canvas_class);
}

void cpd_send_bang(t_cpd_object* obj)
{
    if (!obj) {
        DEBUG("NULL pointer given");
        return;
    }

    pd_bang(&obj->te_g.g_pd);
}

void cpd_send_float(t_cpd_object* obj, t_cpd_float f)
{
    if (!obj) {
        DEBUG("NULL pointer given");
        return;
    }

    pd_float(&obj->te_g.g_pd, f);
}

void cpd_send_symbol(t_cpd_object* obj, t_cpd_symbol* s)
{
    if (!obj || !s) {
        DEBUG("NULL pointer given");
        return;
    }

    pd_symbol(&obj->te_g.g_pd, s);
}

void cpd_send_list(t_cpd_object* obj, const t_cpd_list* l)
{
    if (!obj || !l) {
        DEBUG("NULL pointer given");
        return;
    }

    int n = cpd_list_size(l);
    t_cpd_atom* atoms = cpd_list_at(const_cast<t_cpd_list*>(l), 0);

    pd_list(&obj->te_g.g_pd, &s_list, n, atoms);
}

void cpd_send_message(t_cpd_object* obj, t_cpd_symbol* sel, const t_cpd_list* l)
{
    if (!obj || !sel || !l) {
        DEBUG("NULL pointer given");
        return;
    }

    int n = cpd_list_size(l);
    t_cpd_atom* atoms = cpd_list_at(const_cast<t_cpd_list*>(l), 0);

    pd_typedmess(&obj->te_g.g_pd, sel, n, atoms);
}

t_cpd_object* cpd_object_next(t_cpd_object* obj)
{
    if (!obj) {
        DEBUG("NULL pointer given");
        return nullptr;
    }

    t_gobj* it = obj->te_g.g_next;
    while (it) {
        if (it->g_pd->c_patchable)
            return reinterpret_cast<t_cpd_object*>(it);

        it = it->g_next;
    }

    return nullptr;
}

const char* cpd_object_help_name(t_cpd_object* obj)
{
    if (!obj) {
        DEBUG("NULL pointer given");
        return "";
    }

    return class_gethelpname(obj->te_g.g_pd);
}

const char* cpd_object_help_dir(t_cpd_object* obj)
{
    if (!obj) {
        DEBUG("NULL pointer given");
        return "";
    }

    return class_gethelpdir(obj->te_g.g_pd);
}

t_cpd_object* cpd_object_new_from_string(t_cpd_canvas* c, const char* name, const char* args, int x, int y)
{
    t_cpd_list* alist = cpd_list_new_from_string(args);
    t_cpd_object* obj = cpd_object_new(c, name, alist, x, y);
    cpd_list_free(alist);
    return obj;
}

t_cpd_conn_type cpd_object_inlet_type(t_cpd_object* obj, size_t n)
{
    if (!obj) {
        DEBUG("NULL pointer given");
        return CPD_CONNECTION_CONTROL;
    }

    return obj_issignalinlet(obj, n) ? CPD_CONNECTION_SIGNAL : CPD_CONNECTION_CONTROL;
}

t_cpd_conn_type cpd_object_outlet_type(t_cpd_object* obj, size_t n)
{
    if (!obj) {
        DEBUG("NULL pointer given");
        return CPD_CONNECTION_CONTROL;
    }

    return obj_issignaloutlet(obj, n) ? CPD_CONNECTION_SIGNAL : CPD_CONNECTION_CONTROL;
}

int cpd_is_abstraction(t_cpd_object* obj)
{
    if (!obj) {
        DEBUG("NULL pointer given");
        return 0;
    }

    return cpd_is_canvas(obj) && canvas_isabstraction(reinterpret_cast<t_canvas*>(obj));
}

const char* cpd_object_abstraction_filename(t_cpd_object* obj)
{
    if (!cpd_is_abstraction(obj)) {
        DEBUG("not an abstraction");
        return "";
    }

    t_cpd_canvas* cnv = reinterpret_cast<t_cpd_canvas*>(obj);
    return cpd_canvas_name(cnv);
}

const char* cpd_object_abstraction_dir(t_cpd_object* obj)
{
    if (!cpd_is_abstraction(obj)) {
        DEBUG("not an abstraction");
        return "";
    }

    t_cpd_canvas* patch = reinterpret_cast<t_cpd_canvas*>(obj);

    return canvas_getdir(patch)->s_name;
}

t_cpd_list* cpd_object_method_names(t_cpd_object* obj)
{
    if (!obj) {
        DEBUG("NULL pointers are given");
        return nullptr;
    }

    // get class pointer
    t_class* c = obj->te_g.g_pd;

// handle different struct definitions in <m_impl.h>
#ifdef PDINSTANCE
    t_methodentry* mlist = c->c_methods[pd_this->pd_instanceno];
#else
    t_methodentry* mlist = c->c_methods;
#endif

    const size_t N = size_t(c->c_nmethod);
    auto lst = cpd_list_new(N);

    for (size_t i = 0; i < N; i++) {
        t_methodentry* m = mlist + i;
        cpd_list_set_symbol_at(lst, i, m->me_name);
    }

    return lst;
}

void cpd_bind_object(t_cpd_object* obj, t_cpd_symbol* s)
{
    if ((!obj) || (!s)) {
        DEBUG("NULL pointers are given");
        return;
    }

    pd_bind(&obj->te_g.g_pd, s);
}

void cpd_unbind_object(t_cpd_object* obj, t_cpd_symbol* s)
{
    if ((!obj) || (!s)) {
        DEBUG("NULL pointers are given");
        return;
    }

    pd_unbind(&obj->te_g.g_pd, s);
}

t_cpd_class* cpd_object_class(t_cpd_object* obj)
{
    return obj ? obj->te_g.g_pd : NULL;
}
