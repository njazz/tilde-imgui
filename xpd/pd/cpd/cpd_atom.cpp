#include "cpd_atom.h"
#include "pr_log.h"

#include "m_pd.h"

t_cpd_atom* cpd_atom_float_new(t_cpd_float f)
{
    t_atom* a = new t_atom;
    SETFLOAT(a, f);
    return a;
}

void cpd_atom_free(t_cpd_atom* a)
{
    delete a;
}

t_cpd_atom* cpd_atom_symbol_new(const t_cpd_symbol* s)
{
    t_atom* a = new t_atom;
    SETSYMBOL(a, const_cast<t_cpd_symbol*>(s));
    return a;
}

int cpd_atom_set_float(t_cpd_atom* a, t_cpd_float f)
{
    if (!a)
        return 0;

    SETFLOAT(a, f);
    return 1;
}

int cpd_atom_set_string(t_cpd_atom* a, const char* s)
{
    return cpd_atom_set_symbol(a, cpd_symbol(s));
}

int cpd_atom_is_float(const t_cpd_atom* a)
{
    if (!a)
        return 0;

    return a->a_type == A_FLOAT ? 1 : 0;
}

int cpd_atom_is_symbol(const t_cpd_atom* a)
{
    if (!a)
        return 0;

    return a->a_type == A_SYMBOL ? 1 : 0;
}

t_cpd_float cpd_atom_get_float(const t_cpd_atom* a)
{
    return atom_getfloat(const_cast<t_cpd_atom*>(a));
}

int cpd_atom_set_atom(t_cpd_atom* a, const t_cpd_atom* src)
{
    if (!a || !src) {
        DEBUG("NULL pointers given");
        return 0;
    }

    *a = *src;
    return 1;
}

t_cpd_atom* cpd_atom_string_new(const char* s)
{
    return cpd_atom_symbol_new(cpd_symbol(s));
}

int cpd_atom_set_symbol(t_cpd_atom* a, t_cpd_symbol* s)
{
    if (!a)
        return 0;

    SETSYMBOL(a, s);
    return 1;
}

t_cpd_symbol* cpd_atom_get_symbol(const t_cpd_atom* a)
{
    if (cpd_atom_is_symbol(a))
        return a->a_w.w_symbol;

    return 0;
}

int cpd_atom_equal(const t_cpd_atom* a0, const t_cpd_atom* a1)
{
    if (a0 == a1)
        return 1;

    if (!a0 || !a1)
        return 0;

    if (a0->a_type != a1->a_type)
        return 0;

    if (cpd_atom_is_float(a0))
        return (a0->a_w.w_float == a1->a_w.w_float) ? 1 : 0;

    if (cpd_atom_is_symbol(a0))
        return (a0->a_w.w_symbol == a1->a_w.w_symbol) ? 1 : 0;

    return 0;
}
