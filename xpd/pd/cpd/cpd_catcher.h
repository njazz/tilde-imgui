#ifndef CPD_CATCHER_H
#define CPD_CATCHER_H

#include "cpd_def.h"
#include "cpd_types.h"

#ifdef __cplusplus
extern "C" {
#endif

CPD_EXTERN void cpd_catcher_init();
CPD_EXTERN t_cpd_object* cpd_catcher_new(t_cpd_canvas* cnv);
CPD_EXTERN int cpd_is_catcher(t_cpd_object* c);
CPD_EXTERN int cpd_catcher_empty(t_cpd_object* c);
CPD_EXTERN void cpd_catcher_clear(t_cpd_object* c);
CPD_EXTERN size_t cpd_catcher_count(t_cpd_object* c);
CPD_EXTERN t_cpd_list* cpd_catcher_at(t_cpd_object* c, size_t n);
CPD_EXTERN t_cpd_list* cpd_catcher_last(t_cpd_object* c);
CPD_EXTERN void cpd_catcher_pop(t_cpd_object* c);
CPD_EXTERN int cpd_catcher_last_bang(t_cpd_object* c);
CPD_EXTERN int cpd_catcher_last_float(t_cpd_object* c, t_cpd_float f);
CPD_EXTERN int cpd_catcher_last_symbol(t_cpd_object* c, const char* s);
CPD_EXTERN int cpd_catcher_last_list(t_cpd_object* c, t_cpd_list* l);
CPD_EXTERN int cpd_catcher_last_message(t_cpd_object* c, const char* sel, t_cpd_list* l);
CPD_EXTERN int cpd_catcher_last_string(t_cpd_object* c, const char* str);

#ifdef __cplusplus
}
#endif

#endif // CPD_CATCHER_H
