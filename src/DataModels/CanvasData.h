// (c) 2017 Alex Nadzharov
// License: GPL3

#ifndef CM_CANVAS_TYPES_H
#define CM_CANVAS_TYPES_H

#include "Clipboard.h"
#include "UIPatchcord.hpp"

#include "imgui.h"

#include "pd_localprocess.h"
#include "pd_localserver.h"

#include "PropertyList.h"

class ServerCanvas;

class UiObjectBase;
class UIPatchcord;

typedef std::vector<UiObjectBase*> objectVec;
typedef std::vector<UIPatchcord*> patchcordVec;

////
/// \brief shared canvas data model - boxes, patchcords
class CanvasData {

    objectVec _previouslySelectedBoxes;
    patchcordVec _previouslySelectedPatchcords;

    ImVec2 _position;
    ImVec2 _size;

    PropertyList _properties;

public:
    xpd::CanvasPtr canvas;
    xpd::ProcessPtr pdProcess = 0;

    Clipboard* clipboard = 0;

    objectVec objects = {};
    patchcordVec patchcords = {};

    objectVec selectedObjects = {};
    patchcordVec selectedPatchcords = {};

    std::string fileName = "";
    std::string filePath = "";
    bool firstSave = true;

    bool showGrid = true;
    bool snapToGrid = false;
    int gridStep = 25;

    //
    CanvasData();
//    ~CanvasData();

    //
    inline bool hasObjectsOrPatchcords() { return hasObjects() || hasPatchcords(); }
    inline bool hasObjects() { return ((objects.size() > 0)); }
    inline bool hasPatchcords() { return ((patchcords.size() > 0)); }

    inline bool hasSelectedObjectsOrPatchcords() { return hasSelectedObjects() || hasSelectedPatchcords(); }
    inline bool hasSelectedObjects() { return ((selectedObjects.size() > 0)); }
    inline bool hasSelectedPatchcords() { return ((selectedPatchcords.size() > 0)); }

    // ----------

    PropertyList* properties();

    // ------------------------------

    static void addUniqueObject(objectVec* objects, UiObjectBase* box);
    static void addUniquePatchcord(patchcordVec* patchcords, UIPatchcord* pcord);
    static int findObject(objectVec* objects, UiObjectBase* box);
    static int findPatchcord(patchcordVec* patchcords, UIPatchcord* pcord);

    //
    bool selectObjectsInFrame(ImVec2 start, ImVec2 end);
    void moveSelectedObjects(ImVec2 pos, bool snapToGrid);

    bool objectAtPos(ImVec2 pos);
    //
//
    void selectSingleObject(ImVec2 pos);
//    bool selectObjects();

//    void dragSelectedObjects(ImVec2 delta);

    // ------------------------------

    void addObject(UiObjectBase* box) { addUniqueObject(&objects, box); }
    void addPatchcord(UIPatchcord* pc) { addUniquePatchcord(&patchcords, pc); }

    // ------------------------------

    void selectObject(UiObjectBase* box);
    void selectPatchcord(UIPatchcord* pc);
    void deselectObjects();
    void deselectPatchcords();
    void deselectAll();
    void selectAllObjects();
    void selectAllPatchcords();
    void selectEverything(){};

    // ----------

    void deleteSelectedObjects();
    void deleteSelectedPatchcords();
    void deleteObject(UiObjectBase* obj);
    void deletePatchcord(UIPatchcord* pc);

    // ----------

    void cut();
    void copy();
    void paste();

    // -------

    int findObjectIndex(UiObjectBase* obj);
    UiObjectBase* getObjectByIndex(int idx);

    patchcordVec patchcordsForObject(UiObjectBase* obj);

    // ------------------------------

    std::vector<std::string> canvasContentsAsPdFileStrings(objectVec* objects);
    std::string patchcordAsPdFileString(UIPatchcord* pcord);
    std::vector<std::string> patchcordsAsPdFileStrings(patchcordVec* patchcords);
    std::vector<int> patchcordAsNumbers(UIPatchcord* pcord);

    std::string canvasAsPdFileString();
    std::vector<std::string> canvasContentsAsPdFileStrings();

    std::vector<std::string> asPdFileStrings();

    // -------
};

#endif // CM_CANVAS_TYPES_H
