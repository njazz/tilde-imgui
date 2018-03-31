#ifndef PDSERVERPROTOTYPE_H
#define PDSERVERPROTOTYPE_H

#include <map>
#include <string>
#include <vector>

#include "pd-server_global.h"

typedef std::vector<std::string> ServerPath;

class PDSERVER_EXPORT Observer {
private:
    AtomList* _data;

public:
    Observer();
    virtual void update();

    void setData(AtomList data);
    AtomList* data();
};

class PDSERVER_EXPORT CanvasObserver : public Observer {
public:
    CanvasObserver();

    virtual void inletAdded();
    virtual void inletRemoved();

    virtual void outletAdded();
    virtual void outletRemoved();
};

class PDSERVER_EXPORT PropertyObserver {
public:
    virtual void update();
};

class PDSERVER_EXPORT ConsoleObserver : public Observer {
private:
    string _text;

public:
    void setText(string text) { _text = text; };
    string text() { return _text; };
};

typedef enum { XLetMessage,
    XLetSignal } XLetType;

class PDSERVER_EXPORT ServerXLet {
public:
    XLetType type;
    int index;
};

class PDSERVER_EXPORT ServerOutlet : ServerXLet {
public:
};

class PDSERVER_EXPORT ServerInlet : ServerXLet {
public:
};

// -------------------------------

class PDSERVER_EXPORT ServerProperties {
    vector<PropertyObserver*> _observers;

public:
    void addObserver(PropertyObserver* p);
    void removeObserver(PropertyObserver* p);
};

enum ServerObjectType { typeObject,
    typeCanvas,
    typeArray,
    typeAbstraction };

class PDSERVER_EXPORT ServerCanvas;
typedef struct _text t_object;
typedef struct _symbol t_symbol;

class PDSERVER_EXPORT ServerObject {
private:
    ServerCanvas* _parent;
    ServerObjectType _type;
    ServerProperties* _properties;

    bool _errorBox;

    t_symbol* _receiveSymbol;

public:
    ServerObject();
    ServerObject(t_object* pdObject);

    ~ServerObject();

    // temporary
    t_object* _pdObject;

    bool errorBox() { return _errorBox; }

    bool hasInternalObject() { return _pdObject != 0; }

    explicit ServerObject(ServerCanvas* parent, string text);

    virtual ServerCanvas* parent();

    void message(string str);

    virtual int inletCount();
    virtual int outletCount();

    virtual void registerObserver(Observer* o);
    virtual void deleteObserver();

    ServerObjectType type();
    void setType(ServerObjectType type);

    ServerProperties* properties();

    ServerCanvas* toServerCanvas();

    XLetType getInletType(int index);
    XLetType getOutletType(int index);

    void setReceiveSymbol(string symbolName);
};

typedef struct _serverArrayData {
    int size;
    float* sample;
} ServerArrayData;

class PDSERVER_EXPORT ServerArray : ServerObject {
    int _size;
    string _name;

    ServerCanvas* _parent;

    void* _pdArray;

public:
    explicit ServerArray(ServerCanvas* parent, string name, int size);

    int size();
    void setSize(int size);

    ServerArrayData* getData(); // float* dest, size_t n);
    virtual void registerObserver(Observer* o);
};

class PDSERVER_EXPORT ServerPatchcord {
    t_object* _srcObject;
    t_object* _destObject;
    int _srcOutlet;
    int _destInlet;

public:
    explicit ServerPatchcord(t_object* obj1, int idx1, t_object* obj2, int idx2);
    ~ServerPatchcord();

    t_object* srcObject();
    t_object* destObject();
    int srcOutlet();
    int destInlet();
};

// ----------------------------------------

class PDSERVER_EXPORT ServerInstance;
// typedef struct _glist t_canvas;

class PDSERVER_EXPORT ServerCanvas : public ServerObject {
private:
    struct _glist* _canvas;

    vector<ServerObject*> _objects;
    vector<ServerPatchcord*> _patchcords;
    string _path;

    ServerInstance* _parentInstance;

    CanvasObserver* _observer;

public:
    ServerCanvas();
    ServerCanvas(struct _glist* canvas);

    void setParentInstance(ServerInstance* p) { _parentInstance = p; }
    ServerInstance* parentInstance() { return _parentInstance; }

    ServerObject* createObject(string name); // Object* || Canvas*
    void deleteObject(ServerObject* o);

    struct _glist* canvasObject();

    ServerCanvas* createEmptySubCanvas();

    ServerArray* createArray(string arrayName, int size);
    void deleteArray(ServerArray* a);

    ServerPatchcord* createPatchcord(ServerObject* src, int srcIdx,
        ServerObject* dest, int destIdx); //?
    void deletePatchcord(ServerPatchcord* p);

    vector<ServerObject*> getObjectList();
    vector<ServerPatchcord*> getConnectionList();

    virtual void registerObserver(CanvasObserver* o);
    virtual void deleteObserver();

    virtual int inletCount();
    virtual int outletCount();

    string path();

    void loadbang();

    ServerObject* toServerObject();
};

class PDSERVER_EXPORT ServerAudioDevice {
public:
};

class PDSERVER_EXPORT ServerMIDIDevice {
public:
};

// ----------------------------------------

class PDSERVER_EXPORT ServerInstance // : Object ??
{
private:
    vector<ServerCanvas*> _canvases;
    vector<Observer*> _observers;
    ServerPath* _path;
    ServerAudioDevice* _audioDevice;
    ServerMIDIDevice* _midiDevice;
    ConsoleObserver* _consoleObserver;

public:
    ServerInstance();

    ServerCanvas* createCanvas();
    void deleteCanvas();

    static void dspOn();
    static void dspOff();
    static void dspSwitch(bool value);

    void registerObserver(Observer* o);
    void deleteObserver(Observer* o);

    void setConsoleObserver(ConsoleObserver* o);

    ServerPath* path();

    static string listLoadedLibraries();
    static vector<string> listLoadedClasses();

    void addSearchPath(string searchPath);

    static bool loadLibrary(string libraryName);
    static void loadExternal(string externalName);

    static void post(string text);
    static void error(string text);
    static void verbose(int level, string text);

    static void sendMessage(string object, string text);

    static string getBindObjectsList();

    static void setVerboseLevel(int level);

    ServerAudioDevice* audioDevice();
    ServerMIDIDevice* midiDevice();

    static string getAudioAPIs();
};

// ----------------------------------------

class PDSERVER_EXPORT TheServer {
private:
    vector<ServerInstance*> _instances;

public:
    TheServer();

    vector<ServerInstance*> instances();
    ServerInstance* firstInstance();

    // todo virtual
    ServerInstance* createInstance();
};

class PDSERVER_EXPORT LocalServer : public TheServer {
};

// --------------------------------------

#endif // PDSERVERPROTOTYPE_H
