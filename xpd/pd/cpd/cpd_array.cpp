#include "cpd_array.h"
#include "cpd_array_element.h"
#include "cpd_globals.h"
#include "cpd_types.h"

#include "pr_log.h"

#include "m_pd.h"
extern "C" {
#include "g_canvas.h"
#include "m_imp.h"
#include "s_stuff.h"

t_scalar* garray_getscalar(t_garray* x);
int garray_getname(t_garray* x, t_symbol** namep);
}

#include <algorithm>

t_cpd_array* cpd_array_new(t_cpd_canvas* c, t_cpd_symbol* name, size_t size, int flags)
{
    if (!c) {
        DEBUG("NULL canvas pointer given");
        return 0;
    }

    size = std::max<size_t>(1, size);

    auto arr = graph_array(c, name, &s_float, size, flags);
    canvas_dirty(c, 1);
    return arr;
}

size_t cpd_array_size(t_cpd_array* a)
{
    if (!a) {
        DEBUG("NULL argument");
        return 0;
    }

    t_array* arr = garray_getarray(a);
    if (!arr) {
        DEBUG("Invalid array pointer");
        return 0;
    }

    return arr->a_n;
}

void cpd_array_free(t_cpd_canvas* c, t_cpd_array* arr)
{
    if (!c) {
        ERROR("NULL canvas given");
        return;
    }

    if (!arr) {
        ERROR("NULL array given");
        return;
    }

    glist_delete(c, reinterpret_cast<t_gobj*>(arr));
}

t_cpd_float cpd_array_float_field(t_cpd_array* arr, t_cpd_symbol* name)
{
    if (!arr) {
        DEBUG("NULL array pointer given");
        return 0;
    }

    auto tmpl = template_findbyname(CPD_SYMBOL_TEMPLATE_ARRAY);
    if (!tmpl) {
        DEBUG("couldn't find template {}", CPD_SYMBOL_TEMPLATE_ARRAY->s_name);
        return 0;
    }

    auto scalar = garray_getscalar(arr);
    return template_getfloat(tmpl, name, scalar->sc_vec, 1);
}

int cpd_array_set_float_field(t_cpd_array* arr, t_cpd_symbol* name, t_cpd_float val)
{
    if (!arr) {
        DEBUG("NULL array pointer given");
        return 0;
    }

    auto tmpl = template_findbyname(CPD_SYMBOL_TEMPLATE_ARRAY);
    if (!tmpl) {
        DEBUG("couldn't find template {}", CPD_SYMBOL_TEMPLATE_ARRAY->s_name);
        return 0;
    }

    auto scalar = garray_getscalar(arr);
    template_setfloat(tmpl, name, scalar->sc_vec, val, 1);
    return 1;
}

t_cpd_float cpd_array_linewidth(t_cpd_array* arr)
{
    return cpd_array_float_field(arr, CPD_SYMBOL_ARRAY_LINEWIDTH);
}

int cpd_array_set_linewidth(t_cpd_array* arr, t_cpd_float wd)
{
    return cpd_array_set_float_field(arr, CPD_SYMBOL_ARRAY_LINEWIDTH, wd);
}

t_cpd_array_flags cpd_array_plotstyle(t_cpd_array* arr)
{
    int val = cpd_array_float_field(arr, CPD_SYMBOL_ARRAY_STYLE);
    // see fuzzy flag logic in g_array.c: graph_array
    switch (val) {
    case 0:
        return CPD_ARRAY_STYLE_POLY;
    case 1:
        return CPD_ARRAY_STYLE_POINTS;
    case 2:
        return CPD_ARRAY_STYLE_BEZIER;
    default: {
        DEBUG("unknown array plot style: {}", val);
        return CPD_ARRAY_STYLE_POINTS;
    }
    }
}

int cpd_array_set_plotstyle(t_cpd_array* arr, t_cpd_array_flags style)
{
    int flag = 0;
    switch (style) {
    case CPD_ARRAY_STYLE_POLY:
        flag = 0;
        break;
    case CPD_ARRAY_STYLE_POINTS:
        flag = 1;
        break;
    case CPD_ARRAY_STYLE_BEZIER:
        flag = 2;
        break;
    default:
        DEBUG("unknown style flag: {}", style);
        return 0;
    }

    return cpd_array_set_float_field(arr, CPD_SYMBOL_ARRAY_STYLE, flag);
}

int cpd_array_hidden_name(t_cpd_array* arr)
{
    if (!arr) {
        DEBUG("NULL array pointer given");
        return 0;
    }

    t_symbol* foo;
    return garray_getname(arr, &foo) ? 1 : 0;
}

t_cpd_array* cpd_array_find_by_name(t_cpd_symbol* name)
{
    return reinterpret_cast<t_cpd_array*>(pd_findbyclass(name, garray_class));
}

t_cpd_array_element* cpd_array_element_at(t_cpd_array* arr, size_t n)
{
    if (!arr) {
        DEBUG("NULL array pointer given");
        return nullptr;
    }

    if (n >= garray_npoints(arr)) {
        DEBUG("invalid element index: {}", n);
        return nullptr;
    }

    return &(reinterpret_cast<t_cpd_array_element*>(garray_vec(arr))[n]);
}

int cpd_array_copy_to(t_cpd_array* arr, t_cpd_float* dest, size_t n)
{
    if (!arr || !dest) {
        DEBUG("NULL pointers given");
        return 0;
    }

    int pd_size = 0;
    t_word* data = 0;
    if (!garray_getfloatwords(arr, &pd_size, &data)) {
        DEBUG("can't get array data: {}", cpd_array_name(arr)->s_name);
        return 0;
    }

    const size_t total = std::min(n, size_t(pd_size));

    cpd_elements_copy_floats_to(data, dest, total);
    return 1;
}

t_cpd_symbol* cpd_array_name(t_cpd_array* arr)
{
    t_symbol* res = CPD_SYMBOL_EMPTY;

    if (!arr) {
        DEBUG("NULL array pointer given");
        return res;
    }

    garray_getname(arr, &res);
    return res;
}

int cpd_array_copy_from(t_cpd_array* arr, const t_cpd_float* src, size_t n)
{
    if (!arr || !src) {
        DEBUG("NULL pointers given");
        return 0;
    }

    int pd_size = 0;
    t_word* data = 0;
    if (!garray_getfloatwords(arr, &pd_size, &data)) {
        DEBUG("can't get array data: {}", cpd_array_name(arr)->s_name);
        return 0;
    }

    const size_t total = std::min(n, size_t(pd_size));
    cpd_elements_copy_floats_from(data, src, total);

    return 1;
}

t_cpd_float cpd_array_float_at(t_cpd_array* arr, size_t n)
{
    auto el = reinterpret_cast<t_cpd_array_element*>(garray_vec(arr)) + n;
    return el->w_float;
}

void cpd_array_set_float_at(t_cpd_array* arr, size_t n, t_cpd_float value)
{
    auto el = reinterpret_cast<t_cpd_array_element*>(garray_vec(arr)) + n;
    el->w_float = value;
}

size_t cpd_array_resize(t_cpd_array* a, size_t sz)
{
    const size_t old_size = cpd_array_size(a);

    if (!old_size)
        return 0;

    if (sz < 1) {
        DEBUG("invalid size: {}", sz);
        return 0;
    }

    if (old_size == sz) {
        DEBUG("sizes are equal: {} == {}", old_size, sz);
        return sz;
    }

    garray_resize_long(a, sz);
    return sz;
}
