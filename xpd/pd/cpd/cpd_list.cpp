#include "cpd_list.h"

#include "m_pd.h"
#include "pr_log.h"

#include <vector>

struct _cpd_list {
    std::vector<t_cpd_atom> data;
};

t_cpd_list* cpd_list_new(size_t n)
{
    t_cpd_list* lst = new t_cpd_list;
    if (n) {
        lst->data.assign(n, t_cpd_atom());
    }

    for (size_t i = 0; i < n; i++) {
        SETFLOAT(&lst->data[i], 0);
    }

    return lst;
}

void cpd_list_free(t_cpd_list* l)
{
    if (!l) {
        ERROR("NULL pointer given");
        return;
    }

    delete l;
}

t_cpd_list* cpd_list_new_from_string(const char* s)
{
    t_binbuf* b = binbuf_new();
    binbuf_text(b, s, strlen(s));

    auto ret = new t_cpd_list;

    size_t n = binbuf_getnatom(b);
    t_atom* a = binbuf_getvec(b);

    std::copy(a, a + n, std::back_inserter(ret->data));

    binbuf_free(b);

    return ret;
}

t_cpd_atom* cpd_list_at(t_cpd_list* l, size_t n)
{
    if (!l)
        return 0;

    if (n >= l->data.size())
        return 0;

    return &l->data[n];
}

void cpd_list_clear(t_cpd_list* l)
{
    if (!l)
        return;

    l->data.clear();
}

void cpd_list_append(t_cpd_list* l, const t_cpd_atom* a)
{
    if (!l || !a)
        return;

    l->data.push_back(*a);
}

size_t cpd_list_size(const t_cpd_list* l)
{
    return l ? l->data.size() : 0;
}

t_cpd_list* cpd_list_copy(const t_cpd_list* l)
{
    return l ? (new t_cpd_list(*l)) : NULL;
}

void cpd_list_append_float(t_cpd_list* l, t_cpd_float f)
{
    if (!l) {
        DEBUG("NULL argument");
        return;
    }

    t_atom a;
    SETFLOAT(&a, f);
    l->data.push_back(a);
}

void cpd_list_append_symbol(t_cpd_list* l, t_cpd_symbol* s)
{
    if (!l) {
        DEBUG("NULL argument");
        return;
    }

    t_atom a;
    SETSYMBOL(&a, s);
    l->data.push_back(a);
}

t_cpd_float cpd_list_get_float_at(t_cpd_list* l, size_t idx)
{
    return cpd_atom_get_float(cpd_list_at(l, idx));
}

t_cpd_symbol* cpd_list_get_symbol_at(t_cpd_list* l, size_t n)
{
    return cpd_atom_get_symbol(cpd_list_at(l, n));
}

int cpd_list_set_atom_at(t_cpd_list* l, size_t idx, const t_cpd_atom* a)
{
    return cpd_atom_set_atom(cpd_list_at(l, idx), a);
}

int cpd_list_set_float_at(t_cpd_list* l, size_t idx, t_cpd_float f)
{
    return cpd_atom_set_float(cpd_list_at(l, idx), f);
}

int cpd_list_set_symbol_at(t_cpd_list* l, size_t idx, t_cpd_symbol* s)
{
    return cpd_atom_set_symbol(cpd_list_at(l, idx), s);
}

int cpd_list_equal(t_cpd_list* l0, t_cpd_list* l1)
{
    // self compare
    if (l0 == l1)
        return 1;

    // NULL check
    if (!l0 || !l1)
        return 0;

    if (l0->data.size() != l1->data.size())
        return 0;

    for (size_t i = 0; i < l0->data.size(); i++) {
        if (!cpd_atom_equal(&l0->data[i], &l1->data[i]))
            return 0;
    }

    return 1;
}

void cpd_list_prepend_symbol(t_cpd_list* l, t_cpd_symbol* s)
{
    if (!l) {
        DEBUG("NULL argument");
        return;
    }

    t_atom a;
    SETSYMBOL(&a, s);
    l->data.insert(l->data.begin(), a);
}

void cpd_list_prepend_float(t_cpd_list* l, t_cpd_float f)
{
    if (!l) {
        DEBUG("NULL argument");
        return;
    }

    t_atom a;
    SETFLOAT(&a, f);
    l->data.insert(l->data.begin(), a);
}

char* cpd_list_to_string(t_cpd_list* l)
{
    if (!l) {
        DEBUG("NULL argument");
        return strdup("");
    }

    std::string res;
    size_t argc = cpd_list_size(l);

    for (size_t i = 0; i < argc; i++) {
        if (i != 0)
            res += ' ';

        char buf[MAXPDSTRING];
        atom_string(cpd_list_at(l, i), buf, MAXPDSTRING);

        res += buf;
    }

    return strdup(res.c_str());
}
