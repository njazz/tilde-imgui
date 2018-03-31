#ifndef CPD_METHOD_H
#define CPD_METHOD_H

#include "cpd_def.h"
#include "cpd_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Returns method name
 * @param m - pointer to method
 * @return method name or empty string 
 */
CPD_EXTERN const char* cpd_method_name(t_cpd_method* m);

CPD_EXTERN int cpd_method_is_varargs(t_cpd_method* m);
CPD_EXTERN size_t cpd_method_arg_count(t_cpd_method* m);
CPD_EXTERN t_cpd_method_arg_type cpd_method_arg_type(t_cpd_method* m, size_t n);

#ifdef __cplusplus
}
#endif

#endif // CPD_METHOD_H
