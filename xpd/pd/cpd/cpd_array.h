#ifndef CPD_ARRAY_H
#define CPD_ARRAY_H

#include "cpd_def.h"
#include "cpd_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Find array by specified name 
 * @param name - array name
 * @return pointer to array or NULL if not found
 */
CPD_EXTERN t_cpd_array* cpd_array_find_by_name(t_cpd_symbol* name);

/**
 * Returns pointer to specified array element
 * @param arr - pointer to array
 * @param n - element position
 * @return pointer to array data or NULL on error
 */
CPD_EXTERN t_cpd_array_element* cpd_array_element_at(t_cpd_array* arr, size_t n);

/**
 * Returns float at specified position
 * @param arr - pointer to array
 * @param n - array position
 * @return float
 * @warning no NULLor bounds checks!
 */
CPD_EXTERN t_cpd_float cpd_array_float_at(t_cpd_array* arr, size_t n);

/**
 * Sets float at specified position
 * @param arr - pointer to array
 * @param n - array position
 * @param value - new value
 * @warning no NULL or bounds checks!
 */
CPD_EXTERN void cpd_array_set_float_at(t_cpd_array* arr, size_t n, t_cpd_float value);

/**
 * Copy array elements to destination
 * @param arr - pointer to array
 * @param dest - pointer to destination float array
 * @param n - number of elements in destination array
 * @return 1 on success, 0 on error
 */
CPD_EXTERN int cpd_array_copy_to(t_cpd_array* arr, t_cpd_float* dest, size_t n);

/**
 * Sets array data from given sour
 * @param arr - pointer to array
 * @param src - pointer to source data
 * @param n - number of elements
 * @return 1 on success, 0 on error
 */
CPD_EXTERN int cpd_array_copy_from(t_cpd_array* arr, const t_cpd_float* src, size_t n);

/**
 * Returns array size
 * @param a - pointer to array
 * @return array size or 0 on error
 */
CPD_EXTERN size_t cpd_array_size(t_cpd_array* a);

/**
 * Resizes array
 * @param a - pointer to array
 * @param sz - new size
 * @return new size or 0 on error
 */
CPD_EXTERN size_t cpd_array_resize(t_cpd_array* a, size_t sz);

/**
 * Returns array name
 * @param arr - pointer to array
 * @return array name or CPD_SYMBOL_EMPTY on error
 */
CPD_EXTERN t_cpd_symbol* cpd_array_name(t_cpd_array* arr);

/**
 * Create new array
 * @param c - parent canvas
 * @param name - array name
 * @param size - array size (>0)
 * @param flags - t_cpd_array_flags
 * @return pointer to new array 
 */
CPD_EXTERN t_cpd_array* cpd_array_new(t_cpd_canvas* c, t_cpd_symbol* name, size_t size, int flags);

/**
 * Free array
 * @param c - pointer to parent canvas
 * @param arr - pointer to array
 */
CPD_EXTERN void cpd_array_free(t_cpd_canvas* c, t_cpd_array* arr);

/**
 * Returns array graph line width
 * @param arr - pointer to array
 * @return linewidth (currently 1 or 2) or 0 on error
 */
CPD_EXTERN t_cpd_float cpd_array_linewidth(t_cpd_array* arr);

/**
 * Sets array graph line width
 * @param arr - pointer to array
 * @param wd - new line width
 * @return 1 on success, 0 on error
 */
CPD_EXTERN int cpd_array_set_linewidth(t_cpd_array* arr, t_cpd_float wd);

/**
 * Returns array plot style: CPD_ARRAY_STYLE_POLY, CPD_ARRAY_STYLE_POINTS or CPD_ARRAY_STYLE_BEZIER
 * @param arr - pointer to array
 * @return on error returns 0
 */
CPD_EXTERN t_cpd_array_flags cpd_array_plotstyle(t_cpd_array* arr);

/**
 * Sets flag style
 * @param arr - pointer to array
 * @param style - line style: CPD_ARRAY_STYLE_POLY, CPD_ARRAY_STYLE_POINTS, CPD_ARRAY_STYLE_BEZIER
 * @return 1 on success, 0 on error
 */
CPD_EXTERN int cpd_array_set_plotstyle(t_cpd_array* arr, t_cpd_array_flags style);

/**
 * Checks if array name should be hidden
 * @param arr - pointer to array
 * @return 1 if true, 0 on false
 */
CPD_EXTERN int cpd_array_hidden_name(t_cpd_array* arr);

/**
 * Returns value of named float field
 * @param arr - pointer to array
 * @param name - field name
 * @return 0 on error
 */
CPD_EXTERN t_cpd_float cpd_array_float_field(t_cpd_array* arr, t_cpd_symbol* name);

/**
 * Sets value of named float field
 * @param arr - pointer to array
 * @param name - field name
 * @return 0 on error, 1 on success
 */
CPD_EXTERN int cpd_array_set_float_field(t_cpd_array* arr, t_cpd_symbol* name, t_cpd_float val);

#ifdef __cplusplus
}
#endif

#endif // CPD_ATOM_H
