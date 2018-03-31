#include "cpd_catcher.h"
#include "cpd_list.h"
#include "cpd_object.h"
#include "pr_log.h"

#include "m_pd.h"
extern "C" {
#include "m_imp.h"
}

#define IS_CATCHER(obj)                \
    if (!cpd_is_catcher(obj)) {        \
        DEBUG("not a catcher object"); \
        return 0;                      \
    }

static const char* CATCHER_CLASS_NAME = "@catcher object@";

#include <vector>
typedef std::vector<t_cpd_list*> message_list;

typedef struct _catcher {
    t_object x_obj;
    message_list* lst;
} t_catcher;

static t_class* catcher_class = 0;

static t_catcher* catcher_new()
{
    t_catcher* x = reinterpret_cast<t_catcher*>(pd_new(catcher_class));
    x->lst = new message_list();
    return x;
}

static void catcher_clear(t_catcher* x)
{
    for (size_t i = 0; i < x->lst->size(); i++)
        cpd_list_free(x->lst->at(i));

    x->lst->clear();
}

static void catcher_free(t_catcher* x)
{
    catcher_clear(x);
    delete x->lst;
    x->lst = 0;
}

static t_cpd_list* catcher_at(t_catcher* x, size_t n)
{
    return n < x->lst->size() ? x->lst->at(n) : 0;
}

static t_cpd_list* catcher_last(t_catcher* x)
{
    return x->lst->empty() ? 0 : x->lst->back();
}

static int catcher_last_bang(t_catcher* x)
{
    if (x->lst->empty())
        return 0;

    auto msg = x->lst->back();
    return cpd_list_size(msg) == 1
        && cpd_list_get_symbol_at(msg, 0) == &s_bang;
}

static int catcher_last_float(t_catcher* x, t_cpd_float f)
{
    if (x->lst->empty())
        return 0;

    auto msg = x->lst->back();
    return cpd_list_size(msg) == 2
        && cpd_list_get_symbol_at(msg, 0) == &s_float
        && cpd_list_get_float_at(msg, 1) == f;
}

static int catcher_last_symbol(t_catcher* x, t_cpd_symbol* s)
{
    if (x->lst->empty())
        return 0;

    auto msg = x->lst->back();
    return cpd_list_size(msg) == 2
        && cpd_list_get_symbol_at(msg, 0) == &s_symbol
        && cpd_list_get_symbol_at(msg, 1) == s;
}

static int catcher_last_list(t_catcher* x, t_cpd_list* l)
{
    if (x->lst->empty())
        return 0;

    auto msg = x->lst->back();
    const size_t N = cpd_list_size(l);
    if (cpd_list_size(msg) != (N + 1))
        return 0;

    if (cpd_list_get_symbol_at(msg, 0) != &s_list)
        return 0;

    for (size_t i = 0; i < N; i++) {
        auto a0 = cpd_list_at(msg, i + 1);
        auto a1 = cpd_list_at(l, i);
        if (!cpd_atom_equal(a0, a1))
            return 0;
    }

    return 1;
}

static int catcher_last_message(t_catcher* x, t_symbol* sel, t_cpd_list* l)
{
    if (x->lst->empty())
        return 0;

    auto msg = x->lst->back();
    const size_t N = cpd_list_size(l);
    if (cpd_list_size(msg) != (N + 1))
        return 0;

    if (cpd_list_get_symbol_at(msg, 0) != sel)
        return 0;

    for (size_t i = 0; i < N; i++) {
        auto a0 = cpd_list_at(msg, i + 1);
        auto a1 = cpd_list_at(l, i);
        if (!cpd_atom_equal(a0, a1))
            return 0;
    }

    return 1;
}

static int catcher_last_string(t_catcher* x, const char* str)
{
    if (x->lst->empty())
        return 0;

    auto msg = x->lst->back();

    char* txt = 0;
    int size = 0;
    t_binbuf* b = binbuf_new();
    binbuf_add(b, cpd_list_size(msg), cpd_list_at(msg, 0));
    binbuf_gettext(b, &txt, &size);
    binbuf_free(b);

    // txt - not null-terminated string
    std::string res(txt, size);
    t_freebytes(txt, size);

    return res == str;
}

static void catcher_pop(t_catcher* x)
{
    if (x->lst->size() < 1)
        return;

    cpd_list_free(x->lst->back());
    x->lst->pop_back();
}

static void catcher_any(t_catcher* x, t_symbol* sel, int argc, t_atom* argv)
{
    t_cpd_list* msg = cpd_list_new(0);
    cpd_list_append_symbol(msg, sel);

    for (int i = 0; i < argc; i++)
        cpd_list_append(msg, &argv[i]);

    x->lst->push_back(msg);
}

void cpd_catcher_init()
{
    // already initialized
    if (catcher_class)
        return;

    catcher_class = class_new(gensym(CATCHER_CLASS_NAME),
        reinterpret_cast<t_newmethod>(catcher_new),
        reinterpret_cast<t_method>(catcher_free),
        sizeof(t_catcher), 0, A_NULL);

    class_addanything(catcher_class, reinterpret_cast<t_method>(catcher_any));
}

int cpd_is_catcher(t_cpd_object* c)
{
    if (!catcher_class) {
        DEBUG("catcher class is not initialized! You should call cpd_catcher_init() first.");
        return 0;
    }

    if (!c) {
        DEBUG("NULL given");
        return 0;
    }

    return (c->te_g.g_pd->c_name == catcher_class->c_name) ? 1 : 0;
}

size_t cpd_catcher_count(t_cpd_object* c)
{
    IS_CATCHER(c);

    return ((t_catcher*)c)->lst->size();
}

int cpd_catcher_empty(t_cpd_object* c)
{
    IS_CATCHER(c);

    return ((t_catcher*)c)->lst->empty() ? 1 : 0;
}

void cpd_catcher_clear(t_cpd_object* c)
{
    if (!cpd_is_catcher(c)) {
        DEBUG("not a catcher object");
        return;
    }

    catcher_clear((t_catcher*)c);
}

t_cpd_list* cpd_catcher_at(t_cpd_object* c, size_t n)
{
    IS_CATCHER(c);

    return catcher_at((t_catcher*)c, n);
}

t_cpd_list* cpd_catcher_last(t_cpd_object* c)
{
    IS_CATCHER(c);

    return catcher_last((t_catcher*)c);
}

t_cpd_object* cpd_catcher_new(t_cpd_canvas* cnv)
{
    if (!cnv) {
        DEBUG("NULL canvas");
        return nullptr;
    }

    if (!catcher_class) {
        DEBUG("catcher class is not initialized! "
              "You should call cpd_catcher_init() first.");
        return nullptr;
    }

    return cpd_object_new(cnv, CATCHER_CLASS_NAME, 0, 0, 0);
}

void cpd_catcher_pop(t_cpd_object* c)
{
    if (!cpd_is_catcher(c)) {
        DEBUG("not a catcher object");
        return;
    }

    catcher_pop((t_catcher*)c);
}

int cpd_catcher_last_bang(t_cpd_object* c)
{
    IS_CATCHER(c);

    return catcher_last_bang((t_catcher*)c);
}

int cpd_catcher_last_float(t_cpd_object* c, t_cpd_float f)
{
    IS_CATCHER(c);

    return catcher_last_float((t_catcher*)c, f);
}

int cpd_catcher_last_symbol(t_cpd_object* c, const char* s)
{
    IS_CATCHER(c);

    return catcher_last_symbol((t_catcher*)c, gensym(s));
}

int cpd_catcher_last_list(t_cpd_object* c, t_cpd_list* l)
{
    IS_CATCHER(c);

    return catcher_last_list((t_catcher*)c, l);
}

int cpd_catcher_last_message(t_cpd_object* c, const char* sel, t_cpd_list* l)
{
    if (!sel || !l) {
        DEBUG("NULL arguments");
        return 0;
    }

    IS_CATCHER(c);

    return catcher_last_message((t_catcher*)c, gensym(sel), l);
}

int cpd_catcher_last_string(t_cpd_object* c, const char* str)
{
    IS_CATCHER(c);

    return catcher_last_string((t_catcher*)c, str);
}
