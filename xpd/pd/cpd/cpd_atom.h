#ifndef CPD_ATOM_H
#define CPD_ATOM_H

#include "cpd_def.h"
#include "cpd_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Create float atom
 * @param f - atom value
 * @returns pointer to new atom, it should be free via cpd_atom_free 
 */
CPD_EXTERN t_cpd_atom* cpd_atom_float_new(t_cpd_float f);

/**
 * Create symbol atom
 * @param s - symbol value
 * @return  pointer to new atom
 */
CPD_EXTERN t_cpd_atom* cpd_atom_symbol_new(const t_cpd_symbol* s);

/**
 * Create symbol atom from string
 * @param s - string value, that is converted to symbol via cpd_symbol() call
 * @return  pointer to new atom
 */
CPD_EXTERN t_cpd_atom* cpd_atom_string_new(const char* s);

/**
 * Sets atom float value and set it's type to float
 * @param a - pointer to atom
 * @param f - float value
 */
CPD_EXTERN int cpd_atom_set_float(t_cpd_atom* a, t_cpd_float f);

/**
 * Sets atom symbol value and set it's type to symbol
 * @param a - pointer to atom
 * @param s - string value
 */
CPD_EXTERN int cpd_atom_set_string(t_cpd_atom* a, const char* s);

/**
 * Sets atom symbol value and set it's type to symbol
 * @param a - pointer to atom
 * @param s - symbol value
 */
CPD_EXTERN int cpd_atom_set_symbol(t_cpd_atom* a, t_cpd_symbol* s);

/**
 * Sets atom from other atom
 * @param a - destination atom pointer
 * @param src - source atom pointer
 */
CPD_EXTERN int cpd_atom_set_atom(t_cpd_atom* a, const t_cpd_atom* src);

/**
 * Checks if float atom
 * @param a - pointer to atom
 * @return 1 if float, otherwise 0
 */
CPD_EXTERN int cpd_atom_is_float(const t_cpd_atom* a);

/**
 * Checks if symbol atom
 * @param a - pointer to atom
 * @return 1 if symbol, otherwise 0
 */
CPD_EXTERN int cpd_atom_is_symbol(const t_cpd_atom* a);

/**
 * Returns float atom value
 * @param a - pointer to atom
 * @returns float value or 0 if not float, or NULL
 */
CPD_EXTERN t_cpd_float cpd_atom_get_float(const t_cpd_atom* a);

/**
 * Returns symbol atom value
 * @param a - pointer to atom
 * @return pointer to symbol
 */
CPD_EXTERN t_cpd_symbol* cpd_atom_get_symbol(const t_cpd_atom* a);

/**
 * Destruct atom, created via cpd_atom_float etc.
 * @param a - pointer to atom
 */
CPD_EXTERN void cpd_atom_free(t_cpd_atom* a);

/**
 * Checks if atoms are equal
 * @return 1 if atoms are equal, otherwise 0
 */
CPD_EXTERN int cpd_atom_equal(const t_cpd_atom* a0, const t_cpd_atom* a1);

#ifdef __cplusplus
}
#endif

#endif // CPD_ATOM_H
