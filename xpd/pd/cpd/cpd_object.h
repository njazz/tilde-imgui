#ifndef CPD_OBJECT_H
#define CPD_OBJECT_H

#include "cpd_def.h"
#include "cpd_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Creates new object on specified canvas
 * @param c - parent canvas
 * @param name - object name
 * @param args - arguments list structure
 * @param x - X-position on canvas
 * @param y - Y-position on canvas
 * @return pointer to new object or NULL
 */
CPD_EXTERN t_cpd_object* cpd_object_new(t_cpd_canvas* c, const char* name, const t_cpd_list* args, int x, int y);

/**
 * Creates new object on specified canvas with arguments parsed from string
 * @param c - parent canvas
 * @param name - object name
 * @param args - arguments as string
 * @param x - X-position on canvas
 * @param y - Y-position on canvas
 * @return pointer to new object or NULL
 */
CPD_EXTERN t_cpd_object* cpd_object_new_from_string(t_cpd_canvas* c, const char* name, const char* args, int x, int y);

/**
 * @brief Removed object from canvas and frees it
 * @param cnv - object canvas
 * @param obj - obj pointer
 */
CPD_EXTERN void cpd_object_free(t_cpd_canvas* cnv, t_cpd_object* obj);

/**
 * @brief Returns object name
 * @param obj - pointer to object
 * @return object name or empty string on error
 */
CPD_EXTERN const char* cpd_object_name(t_cpd_object* obj);

/**
 * Returns object arguments. Caller should free result
 * @param obj - pointer to object
 */
CPD_EXTERN t_cpd_list* cpd_object_arguments(t_cpd_object* obj);

/**
 * Returns object string representation. 
 * @note Caller should free result string
 * @return NULL pointer on error
 */
CPD_EXTERN const char* cpd_object_text(t_cpd_object* obj);

/**
 * Returns object class
 * @param obj - pointer to object
 * @return pointer to class or NULL on error
 */
CPD_EXTERN t_cpd_class* cpd_object_class(t_cpd_object* obj);

/**
 * Returns object help filename
 * @param obj - pointer to object
 * @return path or empty string on error
 */
CPD_EXTERN const char* cpd_object_help_name(t_cpd_object* obj);

/**
 * Returns object external directory
 * @param obj - pointer to object
 * @return path or empty string on error
 */
CPD_EXTERN const char* cpd_object_help_dir(t_cpd_object* obj);

/**
 * Object x-coord within toplevel
 * @return -1 on error
 * @see cpd_object_ypos(), cpd_object_set_xpos()
 */
CPD_EXTERN int cpd_object_xpos(t_cpd_object* obj);

/**
 * Object y-coord within toplevel
 * @return -1 on error
 * @see cpd_object_xpos(), cpd_object_set_ypos()
 */
CPD_EXTERN int cpd_object_ypos(t_cpd_object* obj);

/**
 * Set object x-coord within toplevel
 * @see cpd_object_xpos()
 */
CPD_EXTERN void cpd_object_set_xpos(t_cpd_object* obj, int x);

/**
 * Set object x-coord within toplevel
 * @see cpd_object_ypos()
 */
CPD_EXTERN void cpd_object_set_ypos(t_cpd_object* obj, int y);

/**
 * Number of inlets in object
 * @param obj - pointer to object
 * @see cpd_object_outlet_count()
 */
CPD_EXTERN size_t cpd_object_inlet_count(t_cpd_object* obj);

/**
 * Returns inlet type
 * @param obj - pointer to object
 * @param n - inlet number
 * @return inlet type or CPD_CONNECTION_CONTROL
 * @see cpd_object_inlet_count();
 */
CPD_EXTERN t_cpd_conn_type cpd_object_inlet_type(t_cpd_object* obj, size_t n);

/**
 * Number of outlets in object
 * @param obj - pointer to object
 * @see cpd_object_inlet_count()
 */
CPD_EXTERN size_t cpd_object_outlet_count(t_cpd_object* obj);

/**
 * Returns outlet type
 * @param obj - pointer to object
 * @param n - outlet number
 * @return inlet type or CPD_CONNECTION_CONTROL
 * @see cpd_object_outlet_count();
 */
CPD_EXTERN t_cpd_conn_type cpd_object_outlet_type(t_cpd_object* obj, size_t n);

/**
 * @brief check if canvas given
 * @param x - pointer to object
 * @return 1 is given object is canvas, otherwise 0
*/
CPD_EXTERN int cpd_is_canvas(t_cpd_object* x);

/**
 * @brief check is object is abstraction
 * @param x - pointer to object
 * @return 1 is abstraction, otherwise returns 0
 */
CPD_EXTERN int cpd_is_abstraction(t_cpd_object* obj);

/**
 * Returns pointer to next object on canvas
 * @param obj - pointer to current object
 * @return pointer to object or NULL if not found
 */
CPD_EXTERN t_cpd_object* cpd_object_next(t_cpd_object* obj);

/**
 * Connects two objects
 * @return 1 on success, 0 on error
 */
CPD_EXTERN int cpd_connect(t_cpd_object* obj1, size_t outno, t_cpd_object* obj2, size_t inno);

/**
 * Disconnects two objects
 * @return 1 on success, 0 on error
 */
CPD_EXTERN int cpd_disconnect(t_cpd_object* obj1, size_t outno, t_cpd_object* obj2, size_t inno);

/**
 * Sends bang to object
 * @see cpd_send_float(), cpd_send_symbol(), cpd_send_list(), cpd_send_message()
 */
CPD_EXTERN void cpd_send_bang(t_cpd_object* obj);

/**
 * Sends float to object
 * @see cpd_send_bang(), cpd_send_symbol(), cpd_send_list(), cpd_send_message()
 */
CPD_EXTERN void cpd_send_float(t_cpd_object* obj, t_cpd_float f);

/**
 * Sends symbol to object
 * @see cpd_send_bang(), cpd_send_float(), cpd_send_list(), cpd_send_message()
 */
CPD_EXTERN void cpd_send_symbol(t_cpd_object* obj, t_cpd_symbol* s);

/**
 * Sends list to object
 * @see cpd_send_bang(), cpd_send_float(), cpd_send_symbol(), cpd_send_message()
 */
CPD_EXTERN void cpd_send_list(t_cpd_object* obj, const t_cpd_list* l);

/**
 * Sends message to object
 * @param obj - pointer to object
 * @param sel - message selector
 * @param l - message argument list
 * @see cpd_send_bang(), cpd_send_float(), cpd_send_symbol(), cpd_send_list()
 */
CPD_EXTERN void cpd_send_message(t_cpd_object* obj, t_cpd_symbol* sel, const t_cpd_list* l);

/**
 * Returns abstraction filename
 * @param obj - pointer to abstraction
 * @return abstraction filename or empty string on error
 * @see cpd_object_abstraction_dir()
 */
CPD_EXTERN const char* cpd_object_abstraction_filename(t_cpd_object* obj);

/**
 * Returns abstraction directory
 * @param obj - pointer to abstraction
 * @return abstraction directory or empty string on error
 * @see cpd_object_abstraction_filename()
 */
CPD_EXTERN const char* cpd_object_abstraction_dir(t_cpd_object* obj);

/**
 * Returns list of object method names
 * @param obj - pointer to object
 * @return 1 on success, 0 on error
 * @note Caller should free (with cpd_list_free()) result
 */
CPD_EXTERN t_cpd_list* cpd_object_method_names(t_cpd_object* obj);

/**
 * Binds Pd object to symbol
 * @param obj - pointer to object, s - symbol
 */
CPD_EXTERN void cpd_bind_object(t_cpd_object* obj, t_cpd_symbol* s);

/**
 * Uninds Pd object to symbol
 * @param obj - pointer to object, s - symbol
 */
CPD_EXTERN void cpd_unbind_object(t_cpd_object* obj, t_cpd_symbol* s);

#ifdef __cplusplus
}
#endif

#endif // CPD_OBJECT_H
