#ifndef CPD_CLASS_H
#define CPD_CLASS_H

#include "cpd_def.h"
#include "cpd_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief cpd_class_name - returns class name
 * @param c - pointer to class
 * @return class name or empty string on error
 */
CPD_EXTERN const char* cpd_class_name(t_cpd_class* c);

/**
 * @brief cpd_class_method_count - returns number of methods supported by class
 * @param c - pointer to object class
 * @return number of methods or 0
 */
CPD_EXTERN size_t cpd_class_method_count(t_cpd_class* c);

/**
 * @brief cpd_class_method_at - returns method 
 * @param c - pointer to object class
 * @param n - method index
 * @return pointer to method or NULL on error
 */
CPD_EXTERN t_cpd_method* cpd_class_method_at(t_cpd_class* c, size_t n);

/**
 * @brief cpd_class_global_list - returns list of available class names
 * @return list or NULL on error
 * @warning caller shoud free result with cpd_list_free()!
 */
CPD_EXTERN t_cpd_list* cpd_class_global_list();

#ifdef __cplusplus
}
#endif

#endif // CPD_CLASS_H
