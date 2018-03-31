#include "cpd_array_element.h"

#include "m_pd.h"

t_cpd_float cpd_element_float(t_cpd_array_element* el)
{
    return el->w_float;
}

t_cpd_float* cpd_element_float_ptr(t_cpd_array_element* el)
{
    return &el->w_float;
}

void cpd_element_set_float(t_cpd_array_element* el, t_cpd_float value)
{
    el->w_float = value;
}

t_cpd_array_element* cpd_element_next(t_cpd_array_element* el)
{
    return el + 1;
}

t_cpd_array_element* cpd_element_prev(t_cpd_array_element* el)
{
    return el - 1;
}

void cpd_elements_copy_floats_from(t_cpd_array_element* el, const t_cpd_float* src, size_t n)
{
    for (size_t i = 0; i < n; i++)
        el[i].w_float = src[i];
}

void cpd_elements_copy_floats_to(const t_cpd_array_element* el, t_cpd_float* dest, size_t n)
{
    for (size_t i = 0; i < n; i++)
        dest[i] = el[i].w_float;
}

void cpd_elements_fill(t_cpd_array_element* el, t_cpd_float value, size_t n)
{
    for (size_t i = 0; i < n; i++)
        el[i].w_float = value;
}

void cpd_elements_map(t_cpd_array_element* el, size_t n, cpd_element_map_fn fn)
{
    for (size_t i = 0; i < n; i++)
        el[i].w_float = fn(el[i].w_float);
}

t_cpd_float cpd_elements_lfold(t_cpd_array_element* el, size_t n, cpd_element_fold_fn fn, t_cpd_float init)
{
    t_cpd_float res = init;

    for (size_t i = 0; i < n; i++) {
        res = fn(res, el[i].w_float);
    }

    return res;
}

t_cpd_float cpd_elements_rfold(t_cpd_array_element* el, size_t n, cpd_element_fold_fn fn, t_cpd_float init)
{
    t_cpd_float res = init;

    for (size_t i = n; i > 0; i--) {
        res = fn(el[i - 1].w_float, res);
    }

    return res;
}

t_cpd_array_element* cpd_element_move(t_cpd_array_element* el, long offset)
{
    return el + offset;
}

ptrdiff_t cpd_element_diff(t_cpd_array_element* e0, t_cpd_array_element* e1)
{
    return e0 - e1;
}
