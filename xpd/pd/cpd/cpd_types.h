#ifndef CPD_TYPES_H
#define CPD_TYPES_H

#include "cpd_def.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef float t_cpd_float;

struct _symbol;
typedef struct _symbol t_cpd_symbol;

/** 
 * t_cpd_float or t_cpd_symbol
 */
struct _atom;
typedef struct _atom t_cpd_atom;

/**
 * list ot t_cpd_atom
 */
struct _cpd_list;
typedef struct _cpd_list t_cpd_list;

/**
 * patchable object
 */
struct _text;
typedef struct _text t_cpd_object;

/**
 * object method
 */
struct _methodentry;
typedef struct _methodentry t_cpd_method;

/**
 * object class
 */
struct _class;
typedef struct _class t_cpd_class;

/**
 * patch, canvas or subpatch
 */
struct _glist;
typedef struct _glist t_cpd_canvas;

/**
 * graphic array
 */
struct _garray;
typedef struct _garray t_cpd_array;

/**
 * array element
 */
union word;
typedef union word t_cpd_array_element;

/**
 * connection between objects
 */
struct _cpd_connection;
typedef struct _cpd_connection t_cpd_connection;

/**
 * list of audio devices
 */
struct _cpd_audio_devlist;
typedef struct _cpd_audio_devlist t_cpd_audio_devlist;

/**
 * connection type enum
 */
typedef enum _cpd_conn_type {
    CPD_CONNECTION_CONTROL = 0, /// control connection
    CPD_CONNECTION_SIGNAL = 1 /// signal connection
} t_cpd_conn_type;

typedef enum _cpd_array_flags {
    // do not change values
    CPD_ARRAY_SAVE_CONTENT = 1, /// save array content in pd file
    CPD_ARRAY_STYLE_POINTS = 0, /// draw array with points
    CPD_ARRAY_STYLE_POLY = 2, /// draw array with lines
    CPD_ARRAY_STYLE_BEZIER = 4, /// draw array with curves
    CPD_ARRAY_HIDE_NAME = 1 << 3 /// hide array name on canvas
} t_cpd_array_flags;

typedef enum _cpd_method_arg_type {
    CPD_ARG_NONE = 0,
    CPD_ARG_FLOAT,
    CPD_ARG_SYMBOL,
    CPD_ARG_POINTER
} t_cpd_method_arg_type;

/**
 * Float map function
 */
typedef t_cpd_float(cpd_element_map_fn)(t_cpd_float);

/**
 * Float fold function
 */
typedef t_cpd_float(cpd_element_fold_fn)(t_cpd_float v, t_cpd_float acc);

/**
 * Creates new symbol from given string. Caller should NOT free result pointer
 * @param str - symbol string
 * @return pointer to internal PureData hash table
 */
CPD_EXTERN t_cpd_symbol* cpd_symbol(const char* str);

/**
 * Returns symbol name. Caller should NOT free result pointer
 * @return pointer to internal PureData string
 */
CPD_EXTERN const char* cpd_symbol_name(const t_cpd_symbol* s);

/**
 * Checks if symbol is binded to object
 * @param s - symbol
 * @return 1 if binded, otherwise 0 
 */
CPD_EXTERN int cpd_symbol_binded(const t_cpd_symbol* s);

#ifdef __cplusplus
}
#endif

#endif // CPD_TYPES_H
