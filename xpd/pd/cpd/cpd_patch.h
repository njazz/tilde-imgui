#ifndef CPD_PATCH_H
#define CPD_PATCH_H

#include "cpd_def.h"
#include "cpd_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Creates new patch
 * @return pointer to new top-level canvas or NULL on error
 * @see cpd_canvas_free()
 */
CPD_EXTERN t_cpd_canvas* cpd_patch_new();

/**
 * Loads patch from filesystem
 * @param name - name of file
 * @param path - patch directory (if NULL given search file in standart search paths)
 * @return pointer to loaded canvas or NULL on error
 */
CPD_EXTERN t_cpd_canvas* cpd_patch_load(const char* name, const char* path);

/**
 * Saves patch to filesystem
 * @param patch - pointer to patch canvas
 * @param name - name of file
 * @param dir - patch directory
 * @return 1 on success, 0 on error
 */
CPD_EXTERN int cpd_patch_save(t_cpd_canvas* patch, const char* name, const char* dir);

/** 
 * @return pointer to last opened patch or NULL if not found
 * @see cpd_patchlist_next(), cpd_patchlist_count()
 */
CPD_EXTERN t_cpd_canvas* cpd_patchlist_last();

/**
 * Returns number of opened patches
 */
CPD_EXTERN size_t cpd_patchlist_count();

/**
  * Returns pointer to next opened patch in list
  * @see cpd_patchlist_last()
  */
CPD_EXTERN t_cpd_canvas* cpd_patchlist_next(t_cpd_canvas* cnv);

/**
 * Returns pointer to opened patch by specified number
 */
CPD_EXTERN t_cpd_canvas* cpd_patchlist_at(size_t n);

/**
  * Returns root canvas directory path or "" on error
  */
CPD_EXTERN const char* cpd_patch_dir(t_cpd_canvas* cnv);

CPD_EXTERN int cpd_patch_xpos(t_cpd_canvas* cnv);
CPD_EXTERN int cpd_patch_ypos(t_cpd_canvas* cnv);

/**
 * Returns root canvas width
 * @param cnv - pointer to canvas
 * @return width or 0 on error
 * @see cpd_patch_height()
 */
CPD_EXTERN int cpd_patch_width(t_cpd_canvas* cnv);

/**
 * Returns root canvas height
 * @param cnv - pointer to canvas
 * @return height or 0 on error
 * @see cpd_patch_width()
 */
CPD_EXTERN int cpd_patch_height(t_cpd_canvas* cnv);

/**
 * Creates new subpatch on given canvas
 * @param parent - pointer to parent canvas
 * @param name - subpatch name
 * @param args - subpatch arguments
 * @param x - subpatch x pos
 * @param y - subpatch y pos
 * @return pointer to create subpatch or NULL on error
 */
CPD_EXTERN t_cpd_canvas* cpd_subpatch_new(t_cpd_canvas* parent,
    const char* name, t_cpd_list* args, int x, int y);

#ifdef __cplusplus
}
#endif

#endif // CPD_PATCH_H
