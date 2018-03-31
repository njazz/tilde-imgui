//#include "pdlib.h"

#include "pdLib.hpp"

//temporary
map<string, t_updateUI>* updateUImap;
#ifdef UNIX
#include <signal.h>
#endif

extern "C" {

#include <g_canvas.h>
#include <m_imp.h>
#include <m_pd.h>
#include <s_stuff.h>

#include <cassert>

EXTERN void pd_init(void);
int sys_startgui(const char* libdir);

//temporary EXTERNals setup
EXTERN void setup_ui0x2emsg();
EXTERN void setup_list0x2eproduct();

//temporary
//t_canvas* cmp_newpatch();
void cmp_closepatch(t_canvas* canvas);

//temporary
extern "C" void setup_ui0x2ebang(void);
extern "C" void setup_ui0x2etoggle(void);
extern "C" void setup_ui0x2emsg(void);
extern "C" void setup_ui0x2efloat(void);
extern "C" void setup_ui0x2escript(void);
extern "C" void setup_ui0x2esliders(void);
extern "C" void setup_ui0x2ematrix(void);

extern "C" void setup_pdclass(void);
extern "C" void setup_pdinstance(void);
extern "C" void setup_pdmethod(void);
extern "C" void setup_pdproperty(void);
extern "C" void setup_pdsignal(void);

// just a list of objects to implement

//EXTERN "C" t_loadlist *sys_loaded;

//EXTERN "C" void setup_ui0x2enumber_tilde(void);

//EXTERN "C" void setup_ui0x2eslider(void);
//EXTERN "C" void setup_ui0x2eradio(void);

//EXTERN "C" void setup_ui0x2ebpfunc(void);
//EXTERN "C" void setup_ui0x2eknob(void);
//EXTERN "C" void setup_ui0x2escope_tilde(void);
//EXTERN "C" void setup_ui0x2espectroscope_tilde(void);

//temporary
EXTERN void uimsg_set_updateUI(t_pd* x, void* uiobj, t_updateUI func);

//EXTERN "C" void setup_ui0x2ecolorpanel(void);
//EXTERN "C" void setup_ui0x2eincdec(void);
//EXTERN "C" void setup_ui0x2ematrix(void);
//EXTERN "C" void setup_ui0x2emenu(void);
//EXTERN "C" void setup_ui0x2emeter_tilde(void);
//EXTERN "C" void setup_ui0x2epreset(void);
//EXTERN "C" void setup_ui0x2erslider(void);
//EXTERN "C" void setup_ui0x2etab(void);
}

#include <stdbool.h>

#include <ceammc_atomlist.h>

#include <sstream>
#include <string>

//#include <QDebug>

using namespace ceammc;
using namespace std;

//static t_pdinstance* cm_pd;

//EXTERN t_pd* newest; /* OK - this should go into a .h file now :) */

// TODO

typedef void (*t_updatePdObjectUI)(t_pd* obj, void* uiobj, AtomList msg);

//void cmp_error(string msg)
//{
//    cout << "## Pd lib error: %s\n"
//         << msg << "\n";
//}

// copied from libpd

void cmp_pdinit()
{
    //pd_init();

    //cout << "##### cmp_pdinit" << endl;

    // copied from libpd
    signal(SIGFPE, SIG_IGN);
    sys_soundin = NULL;
    sys_soundout = NULL;

    // are all these settings necessary?
    sys_schedblocksize = DEFDACBLKSIZE;
    sys_externalschedlib = 0;
    sys_printtostderr = 0;
    sys_usestdpath = 0; // don't use pd_extrapath, only sys_searchpath
    sys_debuglevel = 0;
    sys_verbose = 0;
    sys_noloadbang = 0;
    sys_nogui = 1;
    sys_hipriority = 0;
    sys_nmidiin = 0;
    sys_nmidiout = 0;
    sys_init_fdpoll();

    sys_printhook = 0;

    //sys_time = 0;

    sys_loaded_classes = 0;

    pd_init();

#ifdef USEAPI_PORTAUDIO
    sys_set_audio_api(API_PORTAUDIO); // API_PORTAUDIO
#endif
#ifdef USEAPI_DUMMY
    sys_set_audio_api(API_DUMMY); // API_PORTAUDIO
#endif
    sys_searchpath = NULL;
    sys_startgui(NULL);

    //cm_pd = pdinstance_new();

    //cm_pd = pd_this;

    //cout << ("pd_this \n");

    if (!pd_this)
        cmp_error("Initialization failed");
    else
        cout << ("Pd library initialized: %x") << pd_this << "\n";

    // temporary extra objects
    // should be compiled as externals

    // TODO
    //    setup_ui0x2emsg();
    //    setup_ui0x2efloat();
    //    setup_ui0x2ebang();
    //    setup_ui0x2etoggle();
    //    setup_ui0x2escript();
    //    setup_ui0x2esliders();
    //    setup_ui0x2ematrix();

    //    setup_pdclass();
    //    setup_pdinstance();
    //    setup_pdmethod();
    //    setup_pdproperty();
    //    setup_pdsignal();

    //temporary initialisations
    //    setup_ui0x2ebpfunc();
    //    setup_ui0x2eknob();
    //    setup_ui0x2emsg();
    //    setup_ui0x2enumber_tilde();
    //    setup_ui0x2eradio();
    //    setup_ui0x2escope_tilde();
    //    setup_ui0x2eslider();
    //    setup_ui0x2espectroscope_tilde();

    //cout << ("pd extras\n");

    // init audio
    int indev[MAXAUDIOINDEV], inch[MAXAUDIOINDEV],
        outdev[MAXAUDIOOUTDEV], outch[MAXAUDIOOUTDEV];

    indev[0] = outdev[0] = DEFAULTAUDIODEV;
    inch[0] = 1;
    outch[0] = 2;

    sys_set_audio_settings(1, indev, 1, inch,
        1, outdev, 1, outch, 44100, -1, 1, DEFDACBLKSIZE);
    sched_set_using_audio(SCHED_AUDIO_CALLBACK);

    sys_reopen_audio();

    //hack lol - removes empty canvas with array template and creates an empty new one
    cmp_closepatch(cmp_new_patch());

    //cout << ("## cm_pd: %x") << pd_this << "\n";

    //cout << "audio ins: " << sys_get_inchannels() << " outs: " << sys_get_outchannels() << "\n";
}

void cmp_setprinthook(t_printhook h)
{
    sys_printhook = h;
}

void cmp_bind_object(t_object* obj, t_symbol* s)
{
    //todo check object here

    pd_bind((t_pd*)obj, s);
}

void cmp_bind_canvas(t_canvas* obj, t_symbol* s)
{
    //todo check object here

    pd_bind((t_pd*)obj, s);
}

void cmp_unbind(t_pd* obj, t_symbol* s)
{
    pd_unbind(obj, s);
}

void cmp_add_searchpath(t_symbol* s)
{
    sys_searchpath = namelist_append_files(sys_searchpath, s->s_name);
    post("added path: %s", s->s_name);
}

void cmp_remove_searchpath(t_symbol* s)
{
    //todo
}

bool cmp_is_abstraction(t_object* x)
{
    bool ret = ((pd_class(&x->te_pd) == canvas_class) && canvas_isabstraction((t_canvas*)x));

    //cout << "is abstraction: " << ret << "\n";

    return ret;
}

bool cmp_is_canvas(t_object* x)
{
    return (pd_class(&x->te_pd) == canvas_class);
}

t_symbol* cmp_get_path(t_canvas* c)
{
    return canvas_getdir(c);
}

string cmp_list_loaded_libraries()
{
    string ret;

    // TODO

    t_loadlist* list = sys_loaded;


    while (list ) {
        ret += string(list->ll_name->s_name) + ",";
        list = list->ll_next;

    }

    return ret;
}

int cmp_loadlib(string name)
{
    sys_load_lib(canvas_getcurrent(), name.c_str());
}

void cmp_clear_searchpath()
{
    sys_searchpath = NULL;
}

#pragma mark -

// --------------------------------

t_canvas* cmp_new_patch()
{
    //cout << ("## new patch for pd instance: %x") << pd_this << "\n";

    AtomList* list = new AtomList;
    *list = Atom(gensym("Untitled-1"));
    list->append(Atom(gensym("~/")));

    t_pd* dest = gensym("pd")->s_thing;
    if (dest == NULL) {
        cmp_error("Pd object not found");
        return 0;
    };

    pd_typedmess(dest, gensym("menunew"), (int)list->size(), list->toPdData());

    t_canvas* ret = 0;
    //ret = (t_canvas*)pd_newest(); //canvas_getcurrent();

    if (pd_this) {

        ret = pd_this->pd_canvaslist->gl_next;

        while (ret->gl_next) {
            //cout << "canvas: " << ret << "\n";
            ret = ret->gl_next;
        }

        //cout << "pd_this: " << pd_this << "\n";
    } else {
        cout << "pd_this ERROR!\n";
    }

    //ret = pd_this->pd_canvaslist;

    //cout << "new canvas: %x" << ret << "\n";

    //pd_typedmess((t_pd*)ret, gensym("dsp"), 1, AtomList(Atom(1.0f)).toPdData());

    canvas_vis(ret, 1);

    return ret;
}

t_canvas* cmp_openpatch(char* filename, char* path)
{
    t_canvas* ret = (t_canvas*)glob_evalfile(0, gensym(filename), gensym(path));

    return ret;
}

void cmp_savepatch(t_canvas* canvas, char* filename, char* path)
{
    t_pd* dest = gensym("pd")->s_thing;
    if (dest == NULL) {
        cmp_error("Pd object not found");
        return;
    };

    AtomList list(Atom(gensym(filename)));
    list.append(Atom(gensym(path)));

    pd_typedmess((t_pd*)canvas, gensym("savetofile"), (int)list.size(), list.toPdData());
}

void cmp_closepatch(t_canvas* canvas)
{
    if (canvas)
        pd_free((t_pd*)canvas);

    //cout << ("closed patch") << "\n'";
}

// --------------------------------

AtomList* stringToAtomList(string in_string)
{
    AtomList* list;

    if (in_string.size()) {
        t_binbuf* nb = binbuf_new();

        binbuf_text(nb, (char*)in_string.c_str(), in_string.size());
        int argc = binbuf_getnatom(nb);
        t_atom* argv = binbuf_getvec(nb);

        list = new AtomList(argc, argv);
    } else {
        list = new AtomList;
    }

    // float workaround

    if (list->size() == 1)
        if (list->at(0).isFloat()) {
            list->insert(0, AtomList(gensym("float")));
        }

    return list;
}

string atomListToString(AtomList* list)
{
    string ret;

    for (int i=0;i<list->size();i++)
    {
        ret += list->at(i).asString()+" ";
    }

    return ret;
}



// --------------------------------

typedef t_object* (*t_newempty)();
typedef t_object* (*t_newfloat)(t_float);
typedef t_object* (*t_newgimme)(t_symbol* s, int argc, t_atom* argv);

t_object* cmp_create_object(t_canvas* canvas, string class_name, int x, int y)
{
    //cout << "create object\n";

    t_object* ret2 = 0;
    t_object* ret1 = 0;

    AtomList* list = stringToAtomList(class_name);
    //cout << "list: " << *list << "\n";

    if (list->size() == 0) {
        delete list;
        return 0;
    }

    list->insert(0, Atom((float)x));
    list->insert(1, Atom((float)y));

    ret1 = (t_object*)pd_newest();

    pd_typedmess((t_pd*)canvas, gensym("obj"), (int)list->size(), list->toPdData());

    // *****************
    /*
    t_symbol* OBJ_NAME = list->at(0).asSymbol(); // gensym(list->at(0).asString());
    t_object* obj_ = 0;
    t_methodentry* m = pd_objectmaker->c_methods;

    list->remove(0);

    for (int i = 0; i < pd_objectmaker->c_nmethod; i++) {
        if (m[i].me_name == OBJ_NAME) {
            if (m[i].me_arg[0] == A_GIMME) {
                t_newgimme new_fn = (t_newgimme)m[i].me_fun;
                t_atom* al = list->toPdData();
                obj_ = (*new_fn)(OBJ_NAME, list->size(), al);
                cout << "GIMME" << endl;
                break;
            }

            if (list->size() > 5) {
                break;
            }

            if (m[i].me_arg[0] == A_NULL) {
                t_newempty new_fn = (t_newempty)m[i].me_fun;
                obj_ = (*new_fn)();
                cout << "NULL" << endl;
                break;
            }

            if (m[i].me_arg[0] == A_DEFFLOAT) {
                t_newfloat new_fn = (t_newfloat)m[i].me_fun;
                t_float f = list->empty() ? 0 : list->at(0).asFloat(0);
                obj_ = (*new_fn)(f);
                cout << "DEFFLOAT" << endl;
                break;
            }

            if (m[i].me_arg[0] == A_FLOAT) {
                t_newfloat new_fn = (t_newfloat)m[i].me_fun;
                t_float f = list->empty() ? 0 : list->at(0).asFloat(0);
                obj_ = (*new_fn)(f);
                cout << "FLOAT" << endl;
                break;
            }
        }
    }

    //assert(obj_);
    */

    t_object* obj_ = (t_object*)pd_newest();

    if (obj_ == ret1) {
        //cout << "object creation error\n";
        cmp_post("object creation error!");
        return 0;
    }

    if (!obj_) {
        //cout << "object creation error\n";
        cmp_post("object creation error!");
        return 0;
    }

    //if (!obj_)

    //ret1 = obj_;

    // *****************

    //    t_gobj* last = ((t_canvas*)canvas)->gl_list;

    //    int fuse_c = 10000;
    //    while (last->g_next && fuse_c) {
    //        last = ((t_canvas*)canvas)->gl_list->g_next;
    //        fuse_c--;
    //    }

    //ret2 = (t_object*)pd_newest();
    //   ret2->te_g = *last;

    //    if (!ret2)
    //        return 0;
    //    if (ret2 != pd_checkobject((t_pd*)ret2))
    //        return 0;
    // ***
    /*
    if (ret2 == ret1)
        return 0;
        */

    //
    //    char* bufp = new char[1024];
    //    int lenp = 0;

    //    binbuf_gettext(ret2->te_binbuf, &bufp, &lenp);
    //    qDebug("object data: %s", bufp);

    //    delete bufp;
    //

    //cout << "class name: " << obj_->te_g.g_pd->c_name->s_name << endl;
    //cout << "class help name: " << ((t_class*)ret2)->c_helpname->s_name << endl;

    //delete list;

    return obj_;
}

void cmp_moveobject(t_object* obj, int x, int y)
{
    obj->te_xpix = x;
    obj->te_ypix = y;
}

void cmp_deleteobject(t_canvas* canvas, t_object* obj)
{

    // one more extra check
    if (canvas) {
        glist_delete(canvas, &obj->te_g);
        //canvas_restoreconnections(glist_getcanvas(canvas));
    } else {
        cout << ("pd canvas not found - not deleted") << "\n";
    }
    cout << ("deleted obj") << "\n";
}

// --------------------------------

void cmp_patchcord(t_object* obj1, int outno, t_object* obj2, int inno)
{
    //qDebug("patchcord");

    obj_connect(obj1, outno, obj2, inno);
}

void cmp_delete_patchcord(t_object* obj1, int outno, t_object* obj2, int inno)
{

    obj_disconnect(obj1, outno, obj2, inno);

} //?

#pragma mark -

// --------------------------------

int cmp_get_outlet_count(t_object* obj)
{
    //qDebug("inlet count for %x", (long)obj);
    return obj_noutlets(obj);
};

int cmp_get_inlet_count(t_object* obj)
{
    return obj_ninlets(obj);
};

#pragma mark -

// --------------------------------

int cmp_get_inlet_type(t_object* obj, int idx)
{
    return obj_issignalinlet(obj, idx);
};

int cmp_get_outlet_type(t_object* obj, int idx)
{
    return obj_issignaloutlet(obj, idx);
};

// --------------------------------
//temporary here

union inletunion {
    t_symbol* iu_symto;
    t_gpointer* iu_pointerslot;
    t_float* iu_floatslot;
    t_symbol** iu_symslot;
    t_float iu_floatsignalvalue;
};

struct _outlet {
    t_object* o_owner;
    struct _outlet* o_next;
    t_outconnect* o_connections;
    t_symbol* o_sym;
};

struct _inlet {
    t_pd i_pd;
    struct _inlet* i_next;
    t_object* i_owner;
    t_pd* i_dest;
    t_symbol* i_symfrom;

    union inletunion i_un;
};

t_outlet* cmp_get_outlet(t_object* x, int idx)
{
    //printf("get outlet\n");
    int n;
    t_outlet* o;
    for (o = x->te_outlet, n = 0; o; o = o->o_next) {

        if (n == idx)
            return o;
        n++;
    }
    return 0;
}

t_inlet* cmp_get_inlet(t_object* x, int idx)
{
    int n;
    t_inlet* o;
    for (o = x->te_inlet, n = 0; o; o = o->i_next) {

        if (n == idx)
            return o;
        n++;
    }
    return 0;
}

#pragma mark -

// --------------------------------------------
// dsp

void cmp_switch_dsp(bool on)
{
    if (!pd_this) {
        cmp_error("library not yet initialized");
        return;
    }

    //cout << "## pd_this: %x" << pd_this << "\n";

    AtomList list;
    list.append(Atom(on ? 1.0f : 0.0f));

    t_pd* dest = gensym("pd")->s_thing;

    if (dest == NULL) {
        cmp_error("Pd object not found");
        return;
    };

    pd_typedmess(dest, gensym("dsp"), (int)list.size(), list.toPdData());

    t_canvas* ret = pd_this->pd_canvaslist->gl_next;

    while (ret->gl_next) {
        //cout << "canvas: " << ret << "\n";
        ret = ret->gl_next;
    }
};

// -------------------------------------------

void cmp_sendstring(t_object* obj, string msg)
{
    //cout << "\n ||| sendstring " << endl;

    AtomList* list = stringToAtomList(msg);

    //cout << "list size: " << list->size() << endl;

    //cout << "list: " << list << endl;

    AtomList list2 = *list; //->subList(1, list->size());
    list2.remove(0);

    //cout << "list2: first element " << list->at(0).asSymbol()->s_name << " size: " << list2.size() << " " << list2 << endl;
    //cout << "pd object: " << obj << endl;

    //cout << "object class name " << ((t_class*)obj)->c_name->s_name << endl;
    //cout << "as symbol: " << list->at(0).asSymbol() << "\n";

    //t_object* o = (t_object*)obj;

    //cout << ("pd_this in sendstring: %x") << pd_this << "\n";

    t_pd* pd = 0;

    if (obj)
        pd = &obj->te_g.g_pd;
    if (pd)
        pd_typedmess(pd, list->at(0).asSymbol(), (int)list2.size(), list2.toPdData());

    //pd_typedmess(obj, gensym("float"), 0, 0);

    delete list;
}

void cmp_post(string text)
{
    post("%s", text.c_str());
}

void cmp_verbose(int level, string text)
{
    verbose(level, text.c_str());
}

void cmp_error(string text)
{
    error(text.c_str());
}

//void cmp_connectUI(t_pd* obj, void* uiobj, t_updateUI func)
//{
//    // fix that !!!

//    // TODO
//    //uimsg_set_updateUI(obj, uiobj, func);
//}

// ---------------------------------------------
// arrays

t_garray* cmp_get_array(t_symbol* arrayname)
{
    t_garray* a = (t_garray*)pd_findbyclass(arrayname, garray_class);
    return a;
}

//todo
void cmp_get_array_data(t_garray* a, int* size, t_word** vec)
{
    //
    garray_getfloatwords(a, size, vec);
}

float* cmp_get_array_data(t_garray* a)
{
    return (float*)garray_vec(a);
}

int cmp_get_array_size(t_garray* a)
{
    return garray_npoints(a);
}

t_garray* cmp_new_array(t_canvas* c, t_symbol* name, t_floatarg size, t_floatarg save, t_floatarg newgraph)
{
    //possibly unused at all
    t_garray* ret;
    glist_arraydialog(c, name, size, save, newgraph);

    ret = cmp_get_array(name); //(t_garray*)pd_newest();
    return ret;
}

// --------------------------------

void cmp_set_verbose(int v)
{
    sys_verbose = v;
}

// --------------------------------

void cmp_loadbang(t_canvas* canvas)
{
    cout << "cmp_loadbang"
         << "\n";
    canvas_loadbang(canvas);
}

// --------------------------------

t_cmp_audio_info* cmp_get_audio_device_info()
{
    t_cmp_audio_info* ret = new t_cmp_audio_info;

    char* indevlist = new char[32 * 1024];
    char* outdevlist = new char[32 * 1024];

    const int maxndev = 32;
    const int devdescsize = 1024;

    sys_get_audio_devs(indevlist, &ret->inputDeviceCount,
        outdevlist, &ret->outputDeviceCount, &ret->hasMulti, &ret->hasCallback,
        maxndev, devdescsize);

    //cout << indevlist << "||" << outdevlist << "\n";

    //ret->inputDeviceList = string(indevlist,1024);
    //ret->outputDeviceList = string(outdevlist,1024);

    return 0;
}


EXTERN string cmp_get_audio_apis()
{
    //    char* buf = new char[1024];
    //    sys_get_audio_apis(buf);

    string c; // = buf;

#ifdef USEAPI_OSS
    c += "OSS,"; //sprintf(buf + strlen(buf), "{OSS %d} ", API_OSS); n++;
#endif
#ifdef USEAPI_MMIO
    c += "standard (MMIO),"; //sprintf(buf + strlen(buf), "{\"standard (MMIO)\" %d} ", API_MMIO); n++;
#endif
#ifdef USEAPI_ALSA
    c += "ALSA,"; // sprintf(buf + strlen(buf), "{ALSA %d} ", API_ALSA); n++;
#endif
#ifdef USEAPI_PORTAUDIO
#ifdef _WIN32
    c += "ASIO (via portaudio),"; //sprintf(buf + strlen(buf),
//"{\"ASIO (via portaudio)\" %d} ", API_PORTAUDIO);
#else
#ifdef __APPLE__
    c += "standard (portaudio) "; //sprintf(buf + strlen(buf),"{\"standard (portaudio)\" %d} ", API_PORTAUDIO);
#else
    c += "portaudio,"; //sprintf(buf + strlen(buf), "{portaudio %d} ", API_PORTAUDIO);
#endif
#endif
#endif

#ifdef USEAPI_JACK
    c += "jack,"; //sprintf(buf + strlen(buf), "{jack %d} ", API_JACK); n++;
#endif
#ifdef USEAPI_AUDIOUNIT
    c += "AudioUnit,"; //sprintf(buf + strlen(buf), "{AudioUnit %d} ", API_AUDIOUNIT); n++;
#endif

#ifdef USEAPI_DUMMY
    c += "dummy,"; //sprintf(buf + strlen(buf), "{dummy %d} ", API_DUMMY); n++;
#endif

    return c;
}

 void* cmp_pdthis()
{
    return pd_this;
}

//

string cmp_list_bind_objects()
{
    string ret = "";

    t_symbol** hashTable = pd_ceammc_gensym_hash_table();

    if (!hashTable) {
        error("hash table error!");
        return "";
    }

    for (int i = 0; i < pd_ceammc_gensym_hash_table_size(); i++) {
        t_symbol* s = hashTable[i];

        if (s) {
            if (s->s_thing) {
                ret += string(s->s_name) + ",";
            }
        }
    }

    return ret;
}

vector<string> cmp_list_loaded_classes()
{
    vector<string> ret;

    // TODO

    t_loaded_classes_list* list = sys_loaded_classes;

    int fuse = 10000;
    while (list && fuse) {
        ret.push_back( string(list->ll_name->s_name) );
        list = list->ll_next;
        fuse--;
    }

    return ret;
}
