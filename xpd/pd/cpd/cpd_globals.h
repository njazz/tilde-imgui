#ifndef CPD_GLOBALS_H
#define CPD_GLOBALS_H

#include "cpd_def.h"
#include "cpd_types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern t_cpd_symbol* CPD_SYMBOL_PD;
extern t_cpd_symbol* CPD_SYMBOL_OBJ;
extern t_cpd_symbol* CPD_SYMBOL_DSP;
extern t_cpd_symbol* CPD_SYMBOL_EMPTY;
extern t_cpd_symbol* CPD_SYMBOL_TEMPLATE_ARRAY;
extern t_cpd_symbol* CPD_SYMBOL_ARRAY_LINEWIDTH;
extern t_cpd_symbol* CPD_SYMBOL_ARRAY_STYLE;

void cpd_globals_init();

#ifdef __cplusplus
}
#endif

#endif // CPD_GLOBALS_H
