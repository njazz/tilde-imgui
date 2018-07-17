#include "Clipboard.h"

//void Clipboard::clear() {}
//void Clipboard::append(std::vector<std::string> data){};

#include "CanvasData.h"

CanvasData::CanvasData(){};
//CanvasData::~CanvasData(){};

// -----

void CanvasData::addUniqueObject(objectVec* objects, UiObjectBase* box){};
void CanvasData::addUniquePatchcord(patchcordVec* patchcords, UIPatchcord* pcord){};
int CanvasData::findObject(objectVec* objects, UiObjectBase* box) { return 1; };
int CanvasData::findPatchcord(patchcordVec* patchcords, UIPatchcord* pcord) { return 1; };

//
bool CanvasData::selectObjectsInFrame(ImVec2 start, ImVec2 end) { return true; };
void CanvasData::moveSelectedObjects(ImVec2 pos, bool snapToGrid){};

bool CanvasData::objectAtPos(ImVec2 pos) { return true; }
//
//
void CanvasData::selectSingleObject(ImVec2 pos){};
//    bool selectObjects();

//    void dragSelectedObjects(ImVec2 delta);

// ------------------------------

//void CanvasData::addObject(UiObjectBase* box) { addUniqueObject(&objects, box); }
//void CanvasData::addPatchcord(UIPatchcord* pc) { addUniquePatchcord(&patchcords, pc); }

// ------------------------------

void CanvasData::selectObject(UiObjectBase* box){};
void CanvasData::selectPatchcord(UIPatchcord* pc){};
void CanvasData::deselectObjects(){};
void CanvasData::deselectPatchcords(){};
void CanvasData::deselectAll(){};
void CanvasData::selectAllObjects(){};
void CanvasData::selectAllPatchcords(){};
//void CanvasData::selectEverything(){};

// ----------

void CanvasData::deleteSelectedObjects(){};
void CanvasData::deleteSelectedPatchcords(){};
void CanvasData::deleteObject(UiObjectBase* obj){};
void CanvasData::deletePatchcord(UIPatchcord* pc){};

// ----------

void CanvasData::cut(){};
void CanvasData::copy(){};
void CanvasData::paste(){};

// -------

int CanvasData::findObjectIndex(UiObjectBase* obj) { return 1; };
UiObjectBase* CanvasData::getObjectByIndex(int idx) { return 0; };

patchcordVec CanvasData::patchcordsForObject(UiObjectBase* obj) { return {}; };

// ------------------------------

std::vector<std::string> CanvasData::canvasContentsAsPdFileStrings(objectVec* objects) { return {}; };
std::string CanvasData::patchcordAsPdFileString(UIPatchcord* pcord) { return ""; };
std::vector<std::string> CanvasData::patchcordsAsPdFileStrings(patchcordVec* patchcords){ return {}; };
std::vector<int> CanvasData::patchcordAsNumbers(UIPatchcord* pcord) { return {}; };

std::string CanvasData::canvasAsPdFileString() { return ""; };
std::vector<std::string> CanvasData::canvasContentsAsPdFileStrings() { return {}; };

std::vector<std::string> CanvasData::asPdFileStrings() { return {}; };
