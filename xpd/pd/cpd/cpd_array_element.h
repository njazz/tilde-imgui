#ifndef CPD_ARRAY_ELEMENT_H
#define CPD_ARRAY_ELEMENT_H

#include "cpd_types.h"

#include <cstddef>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Returns element float value
 * @param el - pointer to element
 * @return float value
 * @note no NULL check
 */
CPD_EXTERN t_cpd_float cpd_element_float(t_cpd_array_element* el);

/**
 * Returns pointer to element float value
 * @param el - pointer to element
 * @return float value
 * @note no NULL check
 */
CPD_EXTERN t_cpd_float* cpd_element_float_ptr(t_cpd_array_element* el);

/**
 * Set array element float value
 * @param el - pointer to element
 * @param value - new value
 * @note no NULL check
 */
CPD_EXTERN void cpd_element_set_float(t_cpd_array_element* el, t_cpd_float value);

/**
 * Returns pointer to next element
 * @param el - pointer to element
 * @return new pointer
 * @note no NULL check
 */
CPD_EXTERN t_cpd_array_element* cpd_element_next(t_cpd_array_element* el);

/**
 * Returns pointer to prev element
 * @param el - pointer to element
 * @return new pointer
 * @note no NULL check
 */
CPD_EXTERN t_cpd_array_element* cpd_element_prev(t_cpd_array_element* el);

/**
 * Moves pointer by offset
 * @param el - pointer to element
 * @return new pointer
 * @note no NULL check
 */
CPD_EXTERN t_cpd_array_element* cpd_element_move(t_cpd_array_element* el, long offset);

/**
 * Returns element difference
 * @param e0
 * @param e1
 * @return 
 */
CPD_EXTERN ptrdiff_t cpd_element_diff(t_cpd_array_element* e0, t_cpd_array_element* e1);

/**
 * Fill element with specified value
 * @param el - pointer to first element
 * @param value - fill value
 * @param n - number of elements
 * @note no range check!
 */
CPD_EXTERN void cpd_elements_fill(t_cpd_array_element* el, t_cpd_float value, size_t n);

/**
 * Copy n elements from source
 * @param el - pointer to first element
 * @param src - pointer to source floats
 * @param n - number of elements
 * @note no range check!
 */
CPD_EXTERN void cpd_elements_copy_floats_from(t_cpd_array_element* el, const t_cpd_float* src, size_t n);

/**
 * Copy n elements to destination
 * @param el - pointer to first element
 * @param src - pointer to source floats
 * @param n - number of elements
 * @note no range check!
 */
CPD_EXTERN void cpd_elements_copy_floats_to(const t_cpd_array_element* el, t_cpd_float* dest, size_t n);

/**
 * Map elements via given function
 * @param el - pointer to first element
 * @param n - number of elements
 * @param fn - map function
 * @note no range check!
 */
CPD_EXTERN void cpd_elements_map(t_cpd_array_element* el, size_t n, cpd_element_map_fn fn);

/**
 * Left fold elements via given function
 * @param el - pointer to first element
 * @param n - number of elements
 * @param fn - fold function
 * @note no range check!
 */
CPD_EXTERN t_cpd_float cpd_elements_lfold(t_cpd_array_element* el, size_t n, cpd_element_fold_fn fn, t_cpd_float init);

/**
 * Right fold elements via given function
 * @param el - pointer to first element
 * @param n - number of elements
 * @param fn - fold function
 * @note no range check!
 */
CPD_EXTERN t_cpd_float cpd_elements_rfold(t_cpd_array_element* el, size_t n, cpd_element_fold_fn fn, t_cpd_float init);

#ifdef __cplusplus
}
#endif

#endif // CPD_ARRAY_ELEMENT_H
