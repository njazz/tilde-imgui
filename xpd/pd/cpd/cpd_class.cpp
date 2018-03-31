#include "cpd_class.h"
#include "cpd_list.h"
#include "pr_log.h"

#include "m_pd.h"
extern "C" {
#include "m_imp.h"
}

t_cpd_method* cpd_class_method_at(t_cpd_class* c, size_t n)
{
    if (!c) {
        ERROR("NULL class pointer given");
        return 0;
    }

    if (n >= c->c_nmethod) {
        WARNING("invalid method index: {}", n);
        return 0;
    }

    return &c->c_methods[n];
}

size_t cpd_class_method_count(t_cpd_class* c)
{
    if (!c) {
        ERROR("NULL class pointer given");
        return 0;
    }

    return c->c_nmethod;
}

const char* cpd_class_name(t_cpd_class* c)
{
    if (!c) {
        ERROR("NULL class pointer given");
        return "";
    }

    return c->c_name->s_name;
}

t_cpd_list* cpd_class_global_list()
{
    const size_t num_classes = cpd_class_method_count(pd_objectmaker);
    t_cpd_list* res = cpd_list_new(num_classes);

    for (size_t i = 0; i < num_classes; i++) {
        auto m = cpd_class_method_at(pd_objectmaker, i);
        if (!m) {
            ERROR("invalid class pointer found");
            cpd_list_free(res);
            return NULL;
        }

        cpd_list_set_symbol_at(res, i, m->me_name);
    }

    return res;
}
