#ifndef CPD_LOADER_H
#define CPD_LOADER_H

#include "cpd_def.h"
#include "cpd_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Tries to load library
 * @param s - library name
 * @return 1 on success, 0 on error
 */
CPD_EXTERN int cpd_load_library(t_cpd_symbol* s);

#ifdef __cplusplus
}
#endif

#endif // CPD_LOADER_H
