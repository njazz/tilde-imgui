#ifndef CPD_CANVAS_H
#define CPD_CANVAS_H

#include "cpd_def.h"
#include "cpd_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Returns canvas name
 */
CPD_EXTERN const char* cpd_canvas_name(t_cpd_canvas* cnv);

/**
 * Returns canvas font size or -1 on error
 */
CPD_EXTERN int cpd_canvas_fontsize(t_cpd_canvas* cnv);

/**
 * Returns pointer to root (top level) parent canvas or 0 if already top
 * @see cpd_canvas_is_root()
 */
CPD_EXTERN t_cpd_canvas* cpd_canvas_root(t_cpd_canvas* cnv);

/**
 * Returns pointer to current canvas
 * @see cpd_canvas_set_current()
 */
CPD_EXTERN t_cpd_canvas* cpd_canvas_current();

/**
 * Push current canvas to current canvas stack
 * @param cnv - pointer to canvas
 * @see cpd_canvas_current()
 */
CPD_EXTERN void cpd_canvas_set_current(t_cpd_canvas* cnv);

/**
 * Pops current canvas from canvas stack
 * @param cnv - pointer to canvas
 * @see cpd_canvas_current()
 */
CPD_EXTERN void cpd_canvas_unset_current(t_cpd_canvas* cnv);

/**
  * Removes canvas
  * @param c - pointer to canvas
  * @see cpd_canvas_new
  */
CPD_EXTERN int cpd_canvas_free(t_cpd_canvas* cnv);

/**
 * Checks if canvas is root (top-level)
 * @return 1 if given canvas is root, 0 otherwise
 * @see cpd_canvas_root()
 */
CPD_EXTERN int cpd_canvas_is_root(t_cpd_canvas* cnv);

/**
 * Returns patchable object on canvas by given index
 * @param cnv - pointer to canvas
 * @param n - object index
 * @return pointer to object or NULL on error
 * @see cpd_canvas_object_count()
 */
CPD_EXTERN t_cpd_object* cpd_canvas_object_at(t_cpd_canvas* cnv, size_t n);

/**
 * Returns number of child element on canvas 
 * @see cpd_canvas_first_object()
 */
CPD_EXTERN size_t cpd_canvas_object_count(t_cpd_canvas* cnv);

/**
 * Returns pointer to first patchable object on canvas
 * @param cnv - pointer to canvas
 * @return pointer to object or NULL if not found
 * @see cpd_canvas_object_count()
 */
CPD_EXTERN t_cpd_object* cpd_canvas_first_object(t_cpd_canvas* cnv);

/**
 * Converts pointer to canvas to pointer to object
 * @param cnv - pointer to canvas
 * @return pointer to object or NULL on error
 */
CPD_EXTERN t_cpd_object* cpd_canvas_to_object(t_cpd_canvas* cnv);

/**
 * Sends the loadbang
 * @param cnv - pointer to canvas
 */
CPD_EXTERN void cpd_canvas_loadbang(t_cpd_canvas* cnv);

#ifdef __cplusplus
}
#endif

#endif // CPD_CANVAS_H
