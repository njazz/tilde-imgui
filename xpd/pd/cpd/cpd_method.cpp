#include "cpd_method.h"
#include "pr_log.h"

#include "m_pd.h"
extern "C" {
#include "m_imp.h"
}

const size_t METHOD_MAX_ARGS = MAXPDARG;

const char* cpd_method_name(t_cpd_method* m)
{
    if (!m) {
        WARNING("NULL method pointer given");
        return "";
    }

    return m->me_name->s_name;
}

size_t cpd_method_arg_count(t_cpd_method* m)
{
    if (!m) {
        WARNING("NULL method pointer given");
        return 0;
    }

    for (size_t i = 0; i < METHOD_MAX_ARGS; i++) {
        if (m->me_arg[i] == A_NULL)
            return i;
    }

    return METHOD_MAX_ARGS;
}

int cpd_method_is_varargs(t_cpd_method* m)
{
    if (!m) {
        WARNING("NULL method pointer given");
        return 0;
    }

    return m->me_arg[0] == A_GIMME ? 1 : 0;
}

t_cpd_method_arg_type cpd_method_arg_type(t_cpd_method* m, size_t n)
{
    if (!m) {
        WARNING("NULL method pointer given");
        return CPD_ARG_NONE;
    }

    if (n >= METHOD_MAX_ARGS) {
        WARNING("invalid argument index");
        return CPD_ARG_NONE;
    }

    switch (m->me_arg[n]) {
    case A_NULL:
        return CPD_ARG_NONE;
    case A_FLOAT:
    case A_DEFFLOAT:
        return CPD_ARG_FLOAT;
    case A_POINTER:
        return CPD_ARG_POINTER;
    case A_SYMBOL:
    case A_DEFSYM:
        return CPD_ARG_SYMBOL;
    default:
        return CPD_ARG_NONE;
    }
}
