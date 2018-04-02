// (c) 2017 Alex Nadzharov
// License: GPL3

#ifndef CM_CANVAS_TYPES_H
#define CM_CANVAS_TYPES_H

#include "Clipboard.h"
#include "UiObjects/UIPatchcord.hpp"

class ServerCanvas;

class ObjectBase;
class UIPatchcord;

class ImVec2;

typedef std::vector<ObjectBase*> objectVec;
typedef std::vector<UIPatchcord*> patchcordVec;

////
/// \brief shared canvas data model - boxes, patchcords
class CanvasData {

    objectVec _previouslySelectedBoxes;
    patchcordVec _previouslySelectedPatchcords;

    //    portItemVec* _inlets;
    //    portItemVec* _outlets;

    // PropertyList* _properties;

    ImVec2 _position;
    ImVec2 _size;

public:
    CanvasData();
    ~CanvasData();

    //    portItemVec* inlets() { return _inlets; }
    //    portItemVec* outlets() { return _outlets; }

    //    void setInlets(portItemVec* inlets) { _inlets = inlets; }
    //    void setOutlets(portItemVec* outlets) { _outlets = outlets; }

    Clipboard* clipboard = 0;

    std::string fileName;
    std::string filePath;
    bool firstSave = true;

    //PropertyList* properties
    //

    //        void
    //        setPosition(QPoint p)
    //    {
    //        _position = p;
    //    }
    //    void setSize(QSize s) { _size = s; }

    //
    bool hasObjects() { return ((objects.size() > 0) || (patchcords.size() > 0)); }
    bool hasSelectedObjects() { return ((selectedObjects.size() > 0) || (selectedPatchcords.size() > 0)); }

    objectVec objects;
    patchcordVec patchcords;

    objectVec selectedObjects;
    patchcordVec selectedPatchcords;

    bool gridSnap = false;

    //    objectVec* boxes() { return &_boxes; }
    //    patchcordVec* patchcords() { return &_patchcords; }
    //    objectVec* selectedBoxes() { return &_selectedBoxes; }
    //    patchcordVec* selectedPatchcords() { return &_selectedPatchcords; }

    // ------------------------------

    void addUniqueObject(objectVec* objects, ObjectBase* box);
    void addUniquePatchcord(patchcordVec* patchcords, UIPatchcord* pcord);
    int findObject(objectVec* objects, ObjectBase* box);
    int findPatchcord(patchcordVec* patchcords, UIPatchcord* pcord);

    //
    bool selectObjectsInFrame(ImVec2 start, ImVec2 end);
    void moveSelectedObjects(ImVec2 pos, bool gridSnap);

    // ------------------------------

    void addObject(ObjectBase* box) { addUniqueObject(&objects, box); }
    void addPatchcord(UIPatchcord* pc) { addUniquePatchcord(&patchcords, pc); }

    // ------------------------------

    void selectObject(ObjectBase* box);
    void selectPatchcord(UIPatchcord* pc);
    void deselectObjects();
    void deselectPatchcords();

    // ----------

    void deletePatchcord(UIPatchcord* pc);

    // ----------

    void cut();
    void copy();
    void paste();

    // -------

    int findObjectIndex(ObjectBase* obj);
    ObjectBase* getObjectByIndex(int idx);
    patchcordVec patchcordsForObject(ObjectBase* obj);

    // ------------------------------

    std::vector<std::string> objectsAsPdFileStrings(objectVec* objects);
    std::string patchcordAsPdFileString(UIPatchcord* pcord);
    std::vector<std::string> patchcordsAsPdFileStrings(patchcordVec* patchcords);
    std::vector<int> patchcordAsNumbers(UIPatchcord* pcord);

    std::vector<std::string> objectsAsPdFileStrings();
    std::string canvasAsPdFileString();
    std::vector<std::string> asPdFileStrings();

    // -------
};

#endif // CM_CANVAS_TYPES_H
