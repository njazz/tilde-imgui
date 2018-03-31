#include "pdServer.hpp"

#include "pdLib.hpp"

#include <algorithm>
#include <cassert>

#include "pd-server_global.h"
// TEMPORARY
//extern "C" {
//#include <m_imp.h>
//#include <m_pd.h>
//}

//TEMPORARY
#include "math.h"

using namespace std;

static vector<pair<long, Observer*> > objectObservers;
// ------------------------------

void Observer::update(){};

void PropertyObserver::update(){};

// -------------------------------

void ServerProperties::addObserver(PropertyObserver* p){};
void ServerProperties::removeObserver(PropertyObserver* p){};

// ---------------------------------------

CanvasObserver::CanvasObserver(){};

void CanvasObserver::inletAdded() { ServerInstance::post("wrong virtual call"); };
void CanvasObserver::inletRemoved(){};
void CanvasObserver::outletAdded(){};
void CanvasObserver::outletRemoved(){};
// ---------------------------------------

ServerObject::ServerObject()
{
    _parent = 0;
    _pdObject = 0;
    _type = typeObject;
    _properties = 0;
    _errorBox = false;
}

ServerObject::ServerObject(t_object* pdObject)
{
    _parent = 0;
    _pdObject = pdObject;
    _type = typeObject;
    _properties = 0;
    _errorBox = false;

    if (_pdObject) {
        if (cmp_is_abstraction((t_object*)_pdObject))
            setType(typeAbstraction);
    } else {
        ServerInstance::error("bad pd object");
    }
}

ServerObject::ServerObject(ServerCanvas* parent, string text)
{

    _parent = parent;
    _pdObject = 0;
    _type = typeObject;
    _properties = 0;

    if (parent->type() == typeCanvas) {

        //        ServerCanvas* p = dynamic_cast<ServerCanvas*>(parent);
        //        assert(p);

        t_canvas* canvas = (parent->canvasObject());

        t_object* obj = cmp_create_object(canvas, text, 0, 0);

        //t_class* cl = (t_class*)obj;

        _pdObject = obj;

        //cout << "|||||||||| new object on canvas: " << canvas << " || pd object ptr " << _pdObject << endl;

        if (obj) {
            //cout << "class name after object is created: " << obj->te_g.g_pd->c_name->s_name << "\n";

            t_class* cl = (t_class*)(obj);

            //t_class
            //cout << "class name after object is created (pointer): " << cl->c_name->s_name << "\n";
        }
    } else {
        cmp_error("ServerCanvas error!");
    }

    _errorBox = (!_pdObject);

    //setType(typeObject);

    if (_pdObject)
        if (cmp_is_abstraction((t_object*)_pdObject))
            setType(typeAbstraction);
}

//void ServerObject::setParent(ServerObject* parent) { _parent = parent; };

ServerCanvas* ServerObject::parent() { return _parent; };

// TEMPORARY
#include "m_imp.h"
void ServerObject::message(string str)
{
    string* msg = new string;
    *msg = str;

    //cout << "msg " << msg << endl;

    t_class* cl = (t_class*)_pdObject;

    //cout << "class name from serverObject: " << cl->c_name->s_name << "\n";

    if (_pdObject) {
        //cout << "send-> " << this << " pd object:" << _pdObject << endl;
        cmp_sendstring(static_cast<t_object*>(_pdObject), *msg);
    } else {
        cmp_error("internal pdObject error");
        //cout << "pdobject error" << endl;
    }
};

int ServerObject::inletCount()
{
    if (_pdObject)
        return cmp_get_inlet_count(reinterpret_cast<t_object*>(_pdObject));
    else
        return -1;
};
int ServerObject::outletCount()
{
    if (_pdObject)
        return cmp_get_outlet_count(reinterpret_cast<t_object*>(_pdObject));
    else
        return -1;
};

void ServerObject::registerObserver(Observer* o)
{
    if (_pdObject) {
        //cout << " ^^^ registered observer: " << (long)o << " for " << (long)_pdObject << "\n";
        objectObservers.push_back(pair<long, Observer*>((long)_pdObject, o));
        //objectObservers[(long)_pdObject] = o;
    }
};

void ServerObject::deleteObserver()
{
    vector<pair<long, Observer*> >::iterator it;
    for (it = objectObservers.begin(); it != objectObservers.end();) {
        pair<long, Observer*> obj = *it;

        if (obj.first == (long)_pdObject) {
            objectObservers.erase(it);
        } else {
            ++it;
        }
    }
};

ServerObjectType ServerObject::type() { return _type; };
void ServerObject::setType(ServerObjectType type) { _type = type; }

ServerProperties* ServerObject::properties() { return _properties; };

//void ServerObject::connectUI(void* uiObject, t_updateUI uiFunction)
//{
//    cmp_connectUI((t_pd*)_pdObject, uiObject, uiFunction);
//};

// if the object is a subpatch, creates a new server object with it and returns it
ServerCanvas* ServerObject::toServerCanvas()
{
    bool isCanvas;
    ServerCanvas* ret = 0;

    if (!_pdObject) {
        isCanvas = false;
        ServerInstance::error("to_server_canvas: bad canvas object!");
    } else
        isCanvas = cmp_is_canvas(_pdObject);

    if (isCanvas) {
        ret = new ServerCanvas((t_canvas*)(_pdObject));
    } else {
        ServerInstance::error("object is not a canvas!");
    }

    return ret;
}

XLetType ServerObject::getInletType(int index)
{
    XLetType ret;

    int i = cmp_get_inlet_type(_pdObject, index);

    if (i)
        ret = XLetSignal;
    else
        ret = XLetMessage;

    return ret;
}

XLetType ServerObject::getOutletType(int index)
{
    XLetType ret;

    int i = cmp_get_outlet_type(_pdObject, index);

    if (i)
        ret = XLetSignal;
    else
        ret = XLetMessage;

    return ret;
}

void ServerObject::setReceiveSymbol(string symbolName)
{
    _receiveSymbol = gensym(symbolName.c_str());

    if (_pdObject)
        cmp_bind_object(_pdObject, _receiveSymbol);
}

ServerObject::~ServerObject()
{
    if (_receiveSymbol)
        cmp_unbind((t_pd*)_pdObject, _receiveSymbol);

    cmp_deleteobject(_parent->canvasObject(), _pdObject);
}

// ----------------------------------------
ServerArray::ServerArray(ServerCanvas* parent, string name, int size)
{
    _name = name;
    _size = size;

    _parent = parent;

    if (!_parent->canvasObject()) {
        ServerInstance::error("ServerArray: bad Pd canvas pointer!");
        //return false;
    }

    //cout << "Array: Pd canvas: " << parent->canvasObject() << "\n";

    _pdArray = cmp_new_array(_parent->canvasObject(), gensym(_name.c_str()), float(_size), 1, 1);

    if (!_pdArray) {
        ServerInstance::error("Pd array not created!");
    }
}
int ServerArray::size()
{
    return _size;
}
void ServerArray::setSize(int size)
{
    _size = size;
}

ServerArrayData* ServerArray::getData() //float* dest, size_t n)
{
    ServerArrayData* ret = new ServerArrayData;

    //int _arrSize = _size;
    if (!_pdArray) {
        ServerInstance::error("bad array pointer!");
        return 0;
    }

    ret->size = _size;

    ret->sample = new float[_size];

    //TEST
    //    for (int i=0;i<_size;i++)
    //    {
    //        ret->sample[i] = sinf(float(i)/_size*6.28);
    //    }

    if (cmp_get_array_size((t_garray*)_pdArray) != _size) {
        ServerInstance::error("Array size error");
    }

    ret->sample = cmp_get_array_data((t_garray*)_pdArray); //, &_size, (t_word**)&ret->sample);

    return ret;
};

void ServerArray::registerObserver(Observer* o){};

// ----------------------------------------

ServerPatchcord::ServerPatchcord(t_object* obj1, int idx1, t_object* obj2, int idx2)
{
    _srcObject = obj1;
    _srcOutlet = idx1;
    _destObject = obj2;
    _destInlet = idx2;
}

ServerPatchcord::~ServerPatchcord()
{
    cmp_delete_patchcord(_srcObject, _srcOutlet, _destObject, _destInlet);
}

t_object* ServerPatchcord::srcObject() { return _srcObject; }
t_object* ServerPatchcord::destObject() { return _destObject; }
int ServerPatchcord::srcOutlet() { return _srcOutlet; }
int ServerPatchcord::destInlet() { return _destInlet; }

// ----------------------------------------
ServerCanvas::ServerCanvas()
{
    _canvas = cmp_new_patch();
    setType(typeCanvas);

    if (!_canvas) {
        ServerInstance::error("bad Pd canvas pointer!");
    } else {
        _path = cmp_get_path(_canvas)->s_name;
    }

    _observer = 0;
}

ServerCanvas::ServerCanvas(t_canvas* canvas)
{
    _canvas = canvas;
    //cout << "|||||||||| server canvas: " << this << " || pd canvas ptr " << _canvas << endl;
    setType(typeCanvas);

    if (!_canvas) {
        ServerInstance::error("bad Pd canvas pointer!");
    } else {
        _path = cmp_get_path(_canvas)->s_name;
    }

    _observer = 0;
}

ServerObject* ServerCanvas::createObject(string name)
{

    ServerObject* ret = new ServerObject(this, name);
    _objects.push_back(ret);

    // this should be done other way

    if (name.substr(0, 5) == "inlet") {
        if (_observer)
            _observer->inletAdded();
        else
            ServerInstance::post("no observer");
    }

    if (name.substr(0, 6) == "outlet") {
        if (_observer)
            _observer->outletAdded();
    }

    return ret;
};

void ServerCanvas::deleteObject(ServerObject* o){
    // TODO

    //    int inCount = toServerObject()->inletCount();
    //    int outCount = toServerObject()->outletCount();

    //    _objects.erase(remove(_objects.begin(), _objects.end(), o), _objects.end());

    //    if (inCount != toServerObject()->inletCount()) {
    //        _observer->inletRemoved();
    //    }

    //    if (outCount != toServerObject()->outletCount()) {
    //        _observer->outletRemoved();
    //    }

};

t_canvas* ServerCanvas::canvasObject()
{
    return _canvas;
}

ServerCanvas* ServerCanvas::createEmptySubCanvas(){};

ServerArray* ServerCanvas::createArray(string arrayName, int size)
{
    ServerArray* ret = new ServerArray(this, arrayName, size);

    return ret;
};
void ServerCanvas::deleteArray(ServerArray* a){};

ServerPatchcord* ServerCanvas::createPatchcord(ServerObject* src, int srcIdx, ServerObject* dest, int destIdx)
{
    ServerPatchcord* ret = new ServerPatchcord((t_object*)src->_pdObject, srcIdx, (t_object*)dest->_pdObject, destIdx);

    // TODO move
    cmp_patchcord((t_object*)src->_pdObject, srcIdx, (t_object*)dest->_pdObject, destIdx);

    return ret;
};

void ServerCanvas::deletePatchcord(ServerPatchcord* p)
{

    // TODO move?
    cmp_delete_patchcord(p->srcObject(), p->srcOutlet(), p->destObject(), p->destInlet());

    delete p;
};

vector<ServerObject*> ServerCanvas::getObjectList()
{
    return _objects;
};
vector<ServerPatchcord*> ServerCanvas::getConnectionList()
{
    return _patchcords;
};

void ServerCanvas::registerObserver(CanvasObserver* o)
{
    _observer = o;
};

void ServerCanvas::deleteObserver(){};

string ServerCanvas::path()
{
    if (!_canvas) {
        ServerInstance::post("canvas_path: server object error!");
        return "";
    }

    //    if (!cmp_is_canvas(_canvas)) {
    //        ServerInstance::post("canvas_path: server canvas error");
    //        return "";
    //    }

    _path = cmp_get_path(_canvas)->s_name;

    return _path;
};

void ServerCanvas::loadbang()
{
    if (_pdObject)
        cmp_loadbang((t_canvas*)_pdObject);
}

ServerObject* ServerCanvas::toServerObject()
{
    ServerObject* ret = 0;

    ret = new ServerObject((t_object*)(_canvas));

    return ret;
}

int ServerCanvas::inletCount()
{
    if (_canvas)
        return cmp_get_inlet_count(reinterpret_cast<t_object*>(_canvas));
    else
        return -1;
}

int ServerCanvas::outletCount()
{
    if (_canvas)
        return cmp_get_outlet_count(reinterpret_cast<t_object*>(_canvas));
    else
        return -1;
}

// -----------------------------------------------

class printHook {
private:
    static vector<ConsoleObserver*> _consoleObservers;

public:
    static void addObserver(ConsoleObserver* c) { _consoleObservers.push_back(c); };
    static void deleteObserver(ConsoleObserver* c){ /*todo*/ };

    static void hookFunction(const char* str)
    {

        vector<ConsoleObserver*>::iterator it;
        for (it = _consoleObservers.begin(); it != _consoleObservers.end(); ++it) {
            ConsoleObserver* c = *it;
            if (c) {
                //cout << "print hook: " << str << endl;
                c->setText(str);
                c->update();
            }
        }
    }
};

vector<ConsoleObserver*> printHook::_consoleObservers;

// ----------------------------------------------

ServerInstance::ServerInstance()
{
    //cout << "######### new server instance" << endl;

    cmp_pdinit();
    cmp_setprinthook(&printHook::hookFunction);

    _consoleObserver = 0;
    _midiDevice = 0;
    _audioDevice = 0;
    _path = 0;
}

ServerCanvas* ServerInstance::createCanvas()
{
    ServerCanvas* ret = new ServerCanvas();
    ret->setParentInstance(this);
    _canvases.push_back(ret);
    return ret;
};

void ServerInstance::deleteCanvas(){
    // TODO
};

void ServerInstance::dspOn() { cmp_switch_dsp(true); };
void ServerInstance::dspOff() { cmp_switch_dsp(false); };
void ServerInstance::dspSwitch(bool value) { cmp_switch_dsp(value); };

void ServerInstance::registerObserver(Observer* o){};
void ServerInstance::deleteObserver(Observer* o){};

void ServerInstance::setConsoleObserver(ConsoleObserver* o)
{
    _consoleObserver = o;

    printHook::addObserver(o);
};

ServerPath* ServerInstance::path() { return _path; };

string ServerInstance::listLoadedLibraries()
{
    return cmp_list_loaded_libraries();
};

vector<string> ServerInstance::listLoadedClasses()
{
    return cmp_list_loaded_classes();
};

void ServerInstance::addSearchPath(string searchPath)
{
    cmp_add_searchpath(gensym(searchPath.c_str()));
}

bool ServerInstance::loadLibrary(string libraryName)
{
    cmp_post("loading library '" + libraryName + "' ...");

    bool ret = cmp_loadlib(libraryName);

    if (!ret)
        cmp_error("Library not loaded: \"" + libraryName + "\"");

    return ret;
};

void ServerInstance::loadExternal(string externalName){};

void ServerInstance::post(string text) { cmp_post(text); };
void ServerInstance::error(string text) { cmp_error(text); };
void ServerInstance::verbose(int level, string text) { cmp_verbose(level, text); };

void ServerInstance::setVerboseLevel(int level)
{
    cmp_set_verbose(level);
};

void ServerInstance::sendMessage(string object, string text)
{
    t_symbol* obj_sym = gensym(object.c_str());

    if (!obj_sym->s_thing) {
        ServerInstance::error("bad destination!");
        return;
    }

    cmp_sendstring((t_object*)obj_sym->s_thing, text);
}

string ServerInstance::getBindObjectsList()
{
    return cmp_list_bind_objects();
}

ServerAudioDevice* ServerInstance::audioDevice() { return _audioDevice; };
ServerMIDIDevice* ServerInstance::midiDevice() { return _midiDevice; };

string ServerInstance::getAudioAPIs() { return cmp_get_audio_apis(); };
// ----------------------------------------

TheServer::TheServer()
{
    createInstance();
}

ServerInstance* TheServer::firstInstance()
{
    if (_instances.size() > 0)
        return _instances[0];
    else
        return 0;
}

vector<ServerInstance*> TheServer::instances() { return _instances; };

ServerInstance* TheServer::createInstance()
{
    ServerInstance* ret = new ServerInstance();
    _instances.push_back(ret);
    return ret;
}

// ---------------------------------------

Observer::Observer()
{
    _data = new AtomList;
}

void Observer::setData(AtomList data) { *_data = data; };

AtomList* Observer::data()
{
    AtomList* ret = new AtomList;
    *ret = *_data;
    return ret;
};

// ---------------------------------------

PDSERVER_EXPORT void qtpdUpdate(long objectId, AtomList list)
{

    vector<pair<long, Observer*> >::iterator it;

    for (it = objectObservers.begin(); it != objectObservers.end(); ++it) {
        pair<long, Observer*> obj = *it;

        if (obj.first == objectId) {
            Observer* o = obj.second;
            if (o) {
                o->setData(list);
                o->update();
            } else {
                cmp_error("observer not found");
            }
        }
        /*else {
        cout << "object not found: " << objectId << "\n";
        cout << "observers count: " << objectObservers.size() << "\n";
    }*/
    }
}
