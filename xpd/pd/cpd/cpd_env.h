#ifndef CPD_ENV_H
#define CPD_ENV_H

#include "cpd_def.h"
#include "cpd_types.h"

#ifdef __cplusplus
extern "C" {
#endif

CPD_EXTERN int cpd_version_major();
CPD_EXTERN int cpd_version_minor();
CPD_EXTERN int cpd_version_bugfix();

CPD_EXTERN void cpd_searchpath_append(const char* path);
CPD_EXTERN size_t cpd_searchpath_num();
CPD_EXTERN const char* cpd_searchpath_at(size_t idx);
CPD_EXTERN void cpd_searchpath_clear();

/** 
 * standard pd hook for print function
 */
typedef void (*t_printhook)(const char* s);

/**
 * @brief connects to print hook function
 * @param h - pointer to function
 */
CPD_EXTERN void cpd_setprinthook(t_printhook h);

#ifdef __cplusplus
}
#endif

#endif // CPD_ENV_H
