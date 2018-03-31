#ifndef CPD_LIST_H
#define CPD_LIST_H

#include "cpd_atom.h"
#include "cpd_def.h"
#include "cpd_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Creates new atomlist of given size initialized with zeroes.
 * @param n - list size
 * @return pointer to allocated list. You should free it with cpd_list_free()
 */
CPD_EXTERN t_cpd_list* cpd_list_new(size_t n);

/**
 * Creates list copy
 * @param l - source list
 * @return pointer to new allocated list or NULL on error
 */
CPD_EXTERN t_cpd_list* cpd_list_copy(const t_cpd_list* l);

/**
 * Free list. NULL pointers are valid
 */
CPD_EXTERN void cpd_list_free(t_cpd_list* l);

/**
 * Removes all element from list, but not frees it
 * @param l - pointer to list
 */
CPD_EXTERN void cpd_list_clear(t_cpd_list* l);

/**
 * Creates new list from given string, parsing it to separate atoms
 * @param s - string
 * @return pointer to alloacted list. You should free it.
 */
CPD_EXTERN t_cpd_list* cpd_list_new_from_string(const char* s);

/**
 * Returns number of elements in list or 0 on error. 
 */
CPD_EXTERN size_t cpd_list_size(const t_cpd_list* l);

/**
 * Returns pointer to element at specified position in list
 * @param l - pointer to list
 * @param n - list position
 * @return pointer to element or NULL on error
 */
CPD_EXTERN t_cpd_atom* cpd_list_at(t_cpd_list* l, size_t n);

/**
 * Returns float at specified position in list
 * @param l - pointer to list
 * @param n - list position
 * @return on error or type mismatch returns 0
 */
CPD_EXTERN t_cpd_float cpd_list_get_float_at(t_cpd_list* l, size_t n);

/**
 * Returns symbol at specified position in list
 * @param l - pointer to list
 * @param n - list position
 * @return on error or type mismatch returns NULL
 */
CPD_EXTERN t_cpd_symbol* cpd_list_get_symbol_at(t_cpd_list* l, size_t n);

/**
 * Appends copy of given atom to the end of list
 * @param l - pointer to list
 * @param a - pointer to attom
 */
CPD_EXTERN void cpd_list_append(t_cpd_list* l, const t_cpd_atom* a);

/**
 * Appends float value to list
 * @param l - pointer to list
 * @param f - float value
 */
CPD_EXTERN void cpd_list_append_float(t_cpd_list* l, t_cpd_float f);

/**
 * Appends symbol value to list
 * @param l - pointer to list
 * @param s - symbol value
 */
CPD_EXTERN void cpd_list_append_symbol(t_cpd_list* l, t_cpd_symbol* s);

/**
 * Prepends float value to list
 * @param l - pointer to list
 * @param f - float value
 */
CPD_EXTERN void cpd_list_prepend_float(t_cpd_list* l, t_cpd_float f);

/**
 * Prepends symbol value to list
 * @param l - pointer to list
 * @param s - symbol value
 */
CPD_EXTERN void cpd_list_prepend_symbol(t_cpd_list* l, t_cpd_symbol* s);

/**
 * Set list element at specified position
 * @param l - pointer to list
 * @param idx - element position
 * @param a - pointer to source atom
 * @return 1 on success or 0 on error
 */
CPD_EXTERN int cpd_list_set_atom_at(t_cpd_list* l, size_t idx, const t_cpd_atom* a);

/**
 * Sets element in list to symbol
 * @param l - pointer to list
 * @param idx - element position
 * @param s - symbol
 * @return 1 on success or 0 on error
 */
CPD_EXTERN int cpd_list_set_symbol_at(t_cpd_list* l, size_t idx, t_cpd_symbol* s);

/**
 * Sets element in list to float at specified position
 * @param l - pointer to list
 * @param idx - element position
 * @param f - float value
 * @return 1 on success or 0 on error
 */
CPD_EXTERN int cpd_list_set_float_at(t_cpd_list* l, size_t idx, t_cpd_float f);

/**
 * Checks if given list are equal: consists from equal elements
 * @return 1 if equal, 0 otherwise
 */
CPD_EXTERN int cpd_list_equal(t_cpd_list* l0, t_cpd_list* l1);

/**
 * Returns list content as string
 * @param l
 * @return pointer to allocated string
 * @warning caller should free result
 */
CPD_EXTERN char* cpd_list_to_string(t_cpd_list* l);

#ifdef __cplusplus
}
#endif

#endif // CPD_LIST_H
