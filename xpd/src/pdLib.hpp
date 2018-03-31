// (c) 2017 Alex Nadzharov
// License: GPL3

#ifndef CM_PDLINK_H
#define CM_PDLINK_H

extern "C" {
#include "m_pd.h"

#include "m_imp.h"
}

#include <map>

typedef void (*t_updateUI)(void *uiobj, ceammc::AtomList msg);

extern std::map<std::string, t_updateUI> *updateUImap;

typedef struct _cmp_audio_info {
  std::string inputDeviceList;
  std::string outputDeviceList;
  int inputDeviceCount;
  int outputDeviceCount;
  int hasMulti;
  int hasCallback;
} t_cmp_audio_info;

// prototype for Pd 'server' interaction

////
/// \brief callback function when UI needs update
///
typedef void (*t_updateUI)(void *uiobj, ceammc::AtomList msg);

////
/// standard pd hook for print function
///
typedef void (*t_printhook)(const char *s);

////
/// \brief initializes pd library
///
extern void cmp_pdinit();

////
/// \brief connects to print hook function
/// \param h - pointer to function
///
extern void cmp_setprinthook(t_printhook h);

////
/// \brief add search path to pd engine
/// \details we do all path handling 'on client' - for canvases we add all the
/// search paths manually \param s
///
extern void cmp_add_searchpath(t_symbol *s);

////
/// \brief remove search path from pd engine
/// \details this is used when canvas is freed to remove temporary search paths
/// \param s
///
extern void cmp_remove_searchpath(t_symbol *s);

////
/// \brief clear search paths
///
extern void cmp_clear_searchpath();

////
/// \brief returns list of loaded externals
/// \return
///
extern std::string cmp_list_loaded_libraries();

////
/// \brief load external
/// \details probably will be removed later
/// \return
///
extern int cmp_loadlib(std::string lib);

#pragma mark -

////
/// \brief creates new t_canvas
/// \return new canvas or 0 if failed
///
extern "C" t_canvas *cmp_new_patch();

////
/// \brief creates canvas from file. TODO probably unused with parser on client
/// app. \param filename \param path \return new canvas or 0 if failed
/// \deprecated not used for now - the files are loaded by 'client'
///
t_canvas *cmp_openpatch(char *filename, char *path);

////
/// \brief saves canvas as pd file
/// \param canvas
/// \param filename
/// \param path
/// \deprecated not used for now - the files are saved by 'client'
///
extern void cmp_savepatch(t_canvas *canvas, char *filename, char *path);

////
/// \brief closes and frees the canvas
/// \param canvas
///
extern "C" void cmp_closepatch(t_canvas *canvas);

////
/// \brief check if canvas is an abstraction
extern bool cmp_is_abstraction(t_object *x);
extern bool cmp_is_canvas(t_object *x);

////
/// \brief get canvas dir if it is an abstraction
extern t_symbol *cmp_get_path(t_canvas *c);

#pragma mark -

////
/// \brief creates pd object
/// \param canvas pointer to canvas
/// \param class_name TODO rename. class name and arguments
/// \param x position
/// \param y position
/// \return pointer to object
///
extern t_object *cmp_create_object(t_canvas *canvas, std::string class_name,
                                   int x, int y);

////
/// \brief creates pd message TODO not working now
/// \param canvas
/// \param message
/// \param x
/// \param y
/// \return pointer to object
/// \deprecated using only objects now
///
// extern t_object* cmp_create_message(t_canvas* canvas, std::string message,
// int x, int y);

////
/// \brief move pd object to new location
/// \param obj
/// \param x
/// \param y
///
extern void cmp_moveobject(t_object *obj, int x, int y);

////
/// \brief delete pd object
/// \param canvas
/// \param obj
///
extern void cmp_deleteobject(t_canvas *canvas, t_object *obj);

////
/// \brief new patchcord
/// \param obj1
/// \param outno
/// \param obj2
/// \param inno
///
extern void cmp_patchcord(t_object *obj1, int outno, t_object *obj2, int inno);

////
/// \brief delete patchcord
/// \param obj1
/// \param outno
/// \param obj2
/// \param inno
///
extern void cmp_delete_patchcord(t_object *obj1, int outno, t_object *obj2,
                                 int inno);

#pragma mark -

////
/// \brief get number of inlets for object
/// \param obj
/// \return inlet count
///
extern int cmp_get_inlet_count(t_object *obj);

////
/// \brief get number of outlets for object
/// \param obj
/// \return outlet count
///
extern int cmp_get_outlet_count(t_object *obj);

////
/// \brief returns inlet at specified index for the object
/// \param obj
/// \param idx
/// \return
///
extern t_inlet *cmp_get_inlet(t_inlet *obj, int idx);

////
/// \brief returns outlet at specified index for the object
/// \param obj
/// \param idx
/// \return
///
extern t_outlet *cmp_get_outlet(t_object *obj, int idx);

////
/// \brief check if inlet is signal~
/// \param obj
/// \param idx
/// \return
///
extern int cmp_get_inlet_type(t_object *obj, int idx);

////
/// \brief check if outlet is signal~
/// \param obj
/// \param idx
/// \return
///
extern int cmp_get_outlet_type(t_object *obj, int idx);

#pragma mark -

////
/// \brief switch dsp on or off
/// \param on
///
extern void cmp_switch_dsp(bool on);

#pragma mark -

////
/// \brief send string as pd message to object
/// \param obj
/// \param msg
///
void cmp_sendstring(t_object *obj, std::string msg);

////
/// \brief set the 'repaint' function of the ui object to be accessible from pd
/// object \param obj \param func
///
void cmp_connectUI(t_pd *obj, void *uiobj, t_updateUI func);

////
/// \brief post plain text to Pd window
/// \param text
///
void cmp_post(std::string text);

////
/// \brief verbose text to Pd window
/// \param text
///
void cmp_verbose(int level, std::string text);

////
/// \brief error text to Pd window
/// \param text
///
void cmp_error(std::string text);

////
/// \brief set verbose level (1..5)
/// \param v
///
void cmp_set_verbose(int v);

///////

////
/// \brief get Pd array pointer by array symbol
/// \param arrayname
/// \return
///
t_garray *cmp_get_array(t_symbol *arrayname);

////
/// \brief get Pd array data
/// \param a
/// \param size
/// \param vec
///
void cmp_get_array_data(t_garray *a, int *size, t_word **vec);
float *cmp_get_array_data(t_garray *a);

////
/// \brief get Pd array size
/// \param a
/// \return
///
int cmp_get_array_size(t_garray *a);

////
/// \brief new Pd array
/// \param c - Pd canvas
/// \param name - array name symbol
/// \param size - minimum size
/// \param save - save within patch - this is unused while we have FileSaver in
/// qtpd_gui \param newgraph - unused \return
///
t_garray *cmp_new_array(t_canvas *c, t_symbol *name, t_floatarg size,
                        t_floatarg save, t_floatarg newgraph);

//
////
/// \brief send loadbang
/// \param canvas
///
EXTERN void cmp_loadbang(t_canvas *canvas);

////
/// \brief Pd audio info structure
// typedef struct _cmp_audio_info {
//    std::string inputDeviceList;
//    std::string outputDeviceList;
//    int inputDeviceCount;
//    int outputDeviceCount;
//    bool hasMulti;
//    bool hasCallback;
//} t_cmp_audio_info;

t_cmp_audio_info *cmp_get_audio_device_info(); /// @brief get audio info structure
std::string cmp_get_audio_apis(); /// @brief get list of audio api names as Tcl string
                                  /// @brief {{api name} {api name 2} ...}

// ------
// debug

void *cmp_pdthis();

//

void cmp_bind_object(t_object *obj, t_symbol *s); ///> bind object to symbol
void cmp_bind_canvas(t_canvas *obj, t_symbol *s); ///> bind canvas to symbol
void cmp_unbind(t_pd *obj, t_symbol *s);          ///> remove binding

std::string cmp_list_bind_objects();

std::vector<std::string> cmp_list_loaded_classes();

#endif // CM_PDLINK_H
