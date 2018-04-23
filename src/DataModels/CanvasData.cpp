// (c) 2017 Alex Nadzharov
// License: GPL3

#include "../UiObjects/UIObject.hpp"

#include "CanvasData.h"
//#include "Preferences.h"

//namespace tilde {
CanvasData::CanvasData()
{
    //_filePath = Preferences::inst().get("Patches");

    //    _properties = new PropertyList();
    //    _properties->create("FixedSize", "Canvas", "0.1", false);

    //    _properties->create("Size", "Canvas", "0.1", QSize(400,300));
    //    _properties->create("Position", "Canvas", "0.1", QPoint(100,100));

    //_properties->create("DrawBoxes", "Canvas", "0.1", false);
}

CanvasData::~CanvasData()
{
    //    delete _properties;
}

void CanvasData::addUniqueObject(objectVec* boxes, UiObjectBase* box)
{
    int p = findObject(boxes, box);

    if (boxes->size())
        if (p >= 0) {
            boxes->erase(boxes->begin() + p);
        }

    boxes->push_back(box);
}

void CanvasData::addUniquePatchcord(patchcordVec* patchcords, UIPatchcord* pcord)
{
    int p = findPatchcord(patchcords, pcord);

    if (patchcords->size())
        if (p >= 0) {
            patchcords->erase(patchcords->begin() + p);
        }

    patchcords->push_back(pcord);
}

int CanvasData::findObject(objectVec* boxes, UiObjectBase* box)
{
    //todo
    for (size_t i = 0; i < boxes->size(); i++) {
        if (boxes->at(i) == box)
            return i;
    }

    return -1;
}

int CanvasData::findPatchcord(patchcordVec* patchcords, UIPatchcord* pcord)
{
    //todo
    for (size_t i = 0; i < patchcords->size(); i++) {
        if (patchcords->at(i) == pcord)
            return i;
    }

    return -1;
}

//void CanvasData::selectBoxesInFrame(ImVec2 start, ImVec2 end)
//{

//    for (int i = 0; i < (int)boxes()->size(); i++) {
//        QPointF pos = ((UIBox*)boxes()->at(i))->pos();

//        QPoint pos_ = QPoint(pos.x(), pos.y());
//        QSizeF size = ((UIBox*)boxes()->at(i))->size();
//        QRect r = QRect(pos_, pos_ + QPoint(size.width(), size.height()));

//        QRect frame = QRect(start, start + end);

//        if (frame.contains(r, false)) {
//            ((UIBox*)boxes()->at(i))->select();
//            //_selectionData.addUniqueBox(_canvasData.boxes()->at(i));
//            selectBox(boxes()->at(i));
//        } else {
//            ((UIBox*)boxes()->at(i))->deselect();

//            auto it = std::find(selectedBoxes()->begin(), selectedBoxes()->end(), boxes()->at(i));
//            if (it != selectedBoxes()->end()) {
//                selectedBoxes()->erase(it);
//            }
//        }
//    }
//}

bool CanvasData::selectObjectsInFrame(ImVec2 start, ImVec2 end)
{
    bool ret = false;
    for (auto o : objects) {
        UIObject* obj = (UIObject*)o;

        obj->data.selected = (obj->x >= start.x);
        obj->data.selected &= (obj->y >= start.y);
        obj->data.selected &= (obj->x <= end.x);
        obj->data.selected &= (obj->y <= end.y);

        ret |= obj->data.selected;
    }
    return ret;
}

void CanvasData::selectObject(UiObjectBase* box)
{
    addUniqueObject(&selectedObjects, box);
    box->data.selected = true;
}

void CanvasData::selectPatchcord(UIPatchcord* pc)
{
    addUniquePatchcord(&selectedPatchcords, pc);
    pc->selected = true;
}

void CanvasData::deselectObjects()
{
    printf("deselect\n");

    _previouslySelectedBoxes = selectedObjects;

    for (int i = 0; i < (int)objects.size(); i++) {
        if (objects.at(i)) {
            ((UiObjectBase*)objects.at(i))->data.selected = false;
        }
    }

    selectedObjects.clear();
}

void CanvasData::deselectPatchcords()
{

    _previouslySelectedPatchcords = selectedPatchcords;
    patchcordVec::iterator it;

    for (auto p : patchcords) {

        p->selected = false;
    }
}

void CanvasData::selectAllObjects()
{
    for (auto o: objects)
        if (!o->data.selected)
            selectObject(o);
}

// ----------

void CanvasData::deleteSelectedObjects()
{
    for (auto o:selectedObjects)
    {
        deleteObject(o);
    }
}

void CanvasData::deleteObject(UiObjectBase* obj)
{
    // todo: remove patchcords for object

    obj->removeFromParentView();
    objects.erase(std::remove(objects.begin(), objects.end(), obj), objects.end());
}

void CanvasData::deletePatchcord(UIPatchcord* pc)
{
    patchcords.erase(std::remove(patchcords.begin(), patchcords.end(), pc), patchcords.end());
}

// ----------

void CanvasData::cut()
{
    clipboard->clear();
    clipboard->append(objectsAsPdFileStrings(&selectedObjects));
    clipboard->append(patchcordsAsPdFileStrings(&selectedPatchcords));

    deleteSelectedObjects();
    deselectObjects();
}

void CanvasData::copy()
{
    clipboard->clear();
    clipboard->append(objectsAsPdFileStrings(&selectedObjects));
    clipboard->append(patchcordsAsPdFileStrings(&selectedPatchcords));
}

void CanvasData::paste()
{
    // todo move here
}

// -------
int CanvasData::findObjectIndex(UiObjectBase* obj)
{
    //UIObject* obj1;
    std::vector<UiObjectBase*>::iterator iter = std::find(objects.begin(), objects.end(), obj);

    size_t index = std::distance(objects.begin(), iter);
    if (index != objects.size()) {
        return index;
    }
    return -1;
}

UiObjectBase* CanvasData::getObjectByIndex(int idx)
{

    if ((idx < (int)objects.size()) && (idx >= 0))
        return objects.at(idx);
    else {
        printf("object not found\n");
        return 0;
    }
}

patchcordVec CanvasData::patchcordsForObject(UiObjectBase* obj)
{
    patchcordVec ret;
    patchcordVec::iterator it;

    for (it = patchcords.begin(); it != patchcords.end(); ++it) {
        if (
            (((UIPatchcord*)*it)->outputObj == obj)
            || (((UIPatchcord*)*it)->inputObj == obj)) {
            ret.push_back(*it);
        }
    }

    return ret;
}

// ------------------------------

std::vector<std::string> CanvasData::objectsAsPdFileStrings(objectVec* boxes)
{
    std::vector<std::string> ret;
    objectVec::iterator it;

    for (it = boxes->begin(); it != boxes->end(); ++it) {

        std::string out1 = ((UIObject*)*it)->asPdFileString();
        out1 += ";\r\n";

        ret.push_back(out1);
    }

    return ret;
}

std::string CanvasData::patchcordAsPdFileString(UIPatchcord* pcord)
{
    //TODO

    int obj1i = findObjectIndex(pcord->outputObj);
    int obj2i = findObjectIndex(pcord->inputObj);

    if ((obj1i >= 0) && (obj2i >= 0)) {
        std::string ret;

        ret += std::to_string(obj1i) + " ";
        ret += std::to_string(pcord->outputIdx) + " ";

        ret += std::to_string(obj2i) + " ";
        ret += std::to_string(pcord->inputIdx) + " ";

        return ret;

    } else
        printf("patchcord to string error\n");

    return "";
}

std::vector<std::string> CanvasData::patchcordsAsPdFileStrings(patchcordVec* patchcords)
{
    std::vector<std::string> ret;
    //patchcordVec patchcords = patchcords;
    patchcordVec::iterator it2;

    for (it2 = patchcords->begin(); it2 != patchcords->end(); ++it2) {
        // check for subpatches
        std::string out1 = "#X connect ";
        out1 += patchcordAsPdFileString(*it2);

        //ut1 = ((Patchcord*)*it2)->asPdFileString();
        out1 += ";\r\n";

        ret.push_back(out1.c_str());
    }

    return ret;
}

std::vector<int> CanvasData::patchcordAsNumbers(UIPatchcord* pcord)
{
    //TODO

    std::vector<int> ret;
    ret.reserve(4);

    int obj1i = findObjectIndex(pcord->outputObj);
    int obj2i = findObjectIndex(pcord->inputObj);

    if ((obj1i >= 0) && (obj2i >= 0)) {
        //std::string ret;

        ret[0] = (obj1i);
        ret[1] = pcord->outputIdx;

        ret[2] = (obj2i);
        ret[3] = pcord->inputIdx;

    } else {
        printf("patchcord to string error\n");
        for (int i = 0; i < 4; i++)
            ret[i] = 0;
    }

    return ret;
}

std::vector<std::string> CanvasData::objectsAsPdFileStrings()
{

    std::vector<std::string> ret = objectsAsPdFileStrings(&objects);
    for (auto s : patchcordsAsPdFileStrings(&patchcords))
        ret.push_back(s);

    return ret;
}

std::string CanvasData::canvasAsPdFileString()
{
    // TODO
    // should be stored by windows

    //return std::string("#N canvas 0 0 400 300 10;\r\n");

    // todo properties
    //    QPoint p = _position; //properties()->get("Position")->asQPoint();
    //    QSize size = _size; //properties()->get("Size")->asQSize();

    // TODO pos
    ImVec2 p = ImVec2(200, 200);
    ImVec2 size = ImVec2(640, 480);

    std::string ret;

    ret = "#N canvas ";
    ret += std::to_string(int(p.x)) + " ";
    ret += std::to_string(int(p.y)) + " ";
    ret += std::to_string(int(size.x)) + " ";
    ret += std::to_string(int(size.y)) + " ";
    ret += "10; \r\n";

    return ret;
}

std::vector<std::string> CanvasData::asPdFileStrings()
{
    std::vector<std::string> ret;
    ret.push_back(canvasAsPdFileString());
    for (auto s : objectsAsPdFileStrings())
        ret.push_back(s);

    return ret;
}
//}
