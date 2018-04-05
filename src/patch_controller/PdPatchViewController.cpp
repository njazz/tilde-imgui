
//
//  PdPatchViewController.cpp
//  imguiController
//
//  Created by Alex on 22/03/2018.
//

#include "PdPatchViewController.hpp"

#include "ArrangeObjects.h"

PdPatchViewController::PdPatchViewController(PdCommonMenus* m)
    : _menu(m)
{

    _emptyObject.addAction(UIObject::oObjectChanged, &objectCreated);
    _emptyObject.addAction(UIObject::oAutocomplete, &autocomplete);
    _emptyObject.hidden = true;
    addSubview(&_emptyObject);

    _menu.common->menuFile.setAction(PdCommonFileMenu::aFileSave, &menuSaveAction);
    _menu.common->menuFile.setAction(PdCommonFileMenu::aFileSaveAs, &menuSaveAsAction);

    _menu.menuEdit.setAction(PdPatchEditMenu::aEditMode, &editModeAction);
    _menu.menuEdit.editModeFlag = &editMode;

    _menu.menuEdit.setAction(PdPatchEditMenu::aCut, &menuCutAction);
    _menu.menuEdit.setAction(PdPatchEditMenu::aCopy, &menuCopyAction);
    _menu.menuEdit.setAction(PdPatchEditMenu::aPaste, &menuPasteAction);

    _menu.menuEdit.setAction(PdPatchEditMenu::aSelectAll, &menuSelectAllAction);

    _menu.menuEdit.setAction(PdPatchEditMenu::aDelete, &menuDeleteObjectAction);

    //

    arrangeLeftAction = IUAction([this]() {
        ArrangeObjects::alignLeft(&data.objects);
    });
    arrangeCenterAction = IUAction([this]() {
        ArrangeObjects::alignCenter(&data.objects);
    });
    arrangeRightAction = IUAction([this]() {
        ArrangeObjects::alignRight(&data.objects);
    });
    arrangeTopAction = IUAction([this]() {
        ArrangeObjects::alignTop(&data.objects);
    });
    arrangeBottomAction = IUAction([this]() {
        ArrangeObjects::alignBottom(&data.objects);
    });

    //

    _menu.menuArrange.showGrid = &data.showGrid;
    _menu.menuArrange.snapToGrid = &data.snapToGrid;

    _menu.menuArrange.setAction(PdPatchArrangeMenu::aAlignLeft, &arrangeLeftAction);
    _menu.menuArrange.setAction(PdPatchArrangeMenu::aAlignCenter, &arrangeCenterAction);
    _menu.menuArrange.setAction(PdPatchArrangeMenu::aAlignRight, &arrangeRightAction);
    _menu.menuArrange.setAction(PdPatchArrangeMenu::aAlignTop, &arrangeTopAction);
    _menu.menuArrange.setAction(PdPatchArrangeMenu::aAlignBottom, &arrangeBottomAction);

    //
    contentSize = ImVec2(width, height);
}

void PdPatchViewController::_drawMenu()
{
    _menu.setWindowController(windowController());
    _menu.common->setWindowController(windowController());
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(4, 4));
    _menu.draw();
    ImGui::PopStyleVar();
}

void PdPatchViewController::setPdProcess(xpd::ProcessPtr p)
{
    data.pdProcess = p;

    if (data.pdProcess)
        data.canvas = data.pdProcess->createCanvas();

    /*
    // test
    createObject("print", 300, 300);

    createObject("pack 0 0 0", 300, 200);
    createObject("unpack 0 0 0 0 0", 300, 250);

    createObject("+", 300, 150);

    auto o1 = createObject("osc~ 440", 50, 150);
    auto o2 = createObject("dac~ 1 2", 50, 300);
    connectObjects(o1, 0, o2, 0);
    connectObjects(o1, 0, o2, 1);

    createObject("ui.toggle", 100, 100);
    createObject("ui.bang", 100, 150);
    createObject("ui.msg", 100, 200);
    createObject("ui.float", 100, 250);
    */
}

void PdPatchViewController::_drawGrid()
{
    // grid
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImVec2 scrolling;
    ImGui::BeginChild(ImGui::GetID("grid"));
    if (editMode && data.showGrid) {
        ImU32 GRID_COLOR = IM_COL32(200, 200, 200, 40);
        float GRID_SZ = data.gridStep; //30.0f;

        ImVec2 win_pos = ImGui::GetCursorScreenPos() - ImVec2(0, 0);
        ImVec2 canvas_sz = ImVec2(contentSize.x, contentSize.y - 20); //ImGui::GetWindowSize();

        for (float x = fmodf(scrolling.x, GRID_SZ); x < contentSize.x; x += GRID_SZ)
            draw_list->AddLine(ImVec2(x, 0.0f) + win_pos, ImVec2(x, contentSize.y - 20) + win_pos, GRID_COLOR);
        for (float y = fmodf(scrolling.y, GRID_SZ); y < contentSize.y - 20; y += GRID_SZ)
            draw_list->AddLine(ImVec2(0.0f, y) + win_pos, ImVec2(contentSize.x, y) + win_pos, GRID_COLOR);
    }
    ImGui::EndChild();
}

void PdPatchViewController::_drawSelectionFrame()
{
    // selection frame

    if (ImGui::IsMouseClicked(0) && editMode) {

        _clickedObject = hitObject(ImGui::GetMousePos()); //&& !_selectionFrame;

        if (_clickedObject && !_multipleObjectsSelected && !_draggingObjects) {
            selectSingleObject(ImGui::GetMousePos());
            _draggingObjects = true;
        }
        _draggingObjects = _clickedObject;

        if (!hitObject(ImGui::GetMousePos()) && !_draggingObjects && (ImGui::GetMousePos().y > 20)) {
            printf("pos %f", ImGui::GetMousePos().y);

            deselectAll();
            _multipleObjectsSelected = false;
            _draggingObjects = false;
        }

        if (!hitObject(ImGui::GetMousePos()) && !_draggingObjects) {

            _selectionStart = _selectionEnd = ImGui::GetMousePos();
            _selectionFrame = true;
        }
    }

    if (_selectionFrame && !ImGui::IsMouseReleased(0)) {
        bool b = selectObjects();
        _multipleObjectsSelected = b;
    }
}

void PdPatchViewController::_drawObjectMaker()
{
    // new empty object
    if (ImGui::IsMouseDoubleClicked(0) && editMode) {
        if (!hitObject(ImGui::GetIO().MousePos)) {
            //addObject("", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
            _emptyObject.x = ImGui::GetIO().MousePos.x;
            _emptyObject.y = ImGui::GetIO().MousePos.y;
            _emptyObject.data.emptyBox = true;
            _emptyObject.data.errorBox = true;
            _emptyObject.pdObject = 0;
            _emptyObject.pdObjectID = 0;
            _emptyObject.objectText = "";
            _emptyObject.hidden = false;
            _emptyObject.clearEditText();
        }
    }
}

void PdPatchViewController::draw()
{
    ImGui::SetNextWindowSize(ImVec2(width, height - 20));

    // temporary!
    resizeToObjects();

    ImGui::SetNextWindowContentSize(contentSize);
    ImGui::SetNextWindowPos(ImVec2(0, 22));

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    bool w = true;
    ImGui::Begin("patch", &w, ImVec2(0,0),0.75, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoTitleBar );

//    ImGui::BeginTooltip();
//    ImGui::Text("contents: %f %f (%f %f)", contentSize.x, contentSize.y, width, height);
//    ImGui::EndTooltip();

    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    _drawMenu();

    _drawGrid();

    _drawSelectionFrame();

    if (ImGui::IsMouseDragging()) {
        if (_draggingObjects) {
            dragSelectedObjects(ImGui::GetIO().MouseDelta);
        } else {
            _selectionFrame &= true;
            _selectionEnd = ImGui::GetMousePos();
        }
    }

    //
    IUViewController::draw();

    if (_selectionFrame) {
        draw_list->AddRectFilled(_selectionStart, _selectionEnd, IM_COL32(0, 168, 192, 128));
    }

    if (ImGui::IsMouseReleased(0)) {
        //        printf("up\n");
        _selectionFrame = false;
        _draggingObjects = false;
    }

    //
    ImVec2 pos = ImGui::GetMousePos();
    _newPatchcord.inputX = pos.x;
    _newPatchcord.inputY = pos.y;
    //ImGui::SetTooltip("pos %f %f",pos.x,pos.y);

    _newPatchcord.draw();

    ImGui::End();
    ImGui::PopStyleVar();

    _drawObjectMaker();

    // deselect patchcord
    if (ImGui::IsMouseClicked(0)) {
        if (!hitObject(ImGui::GetIO().MousePos)) {
            _newPatchcord.outputObj = 0;
        }
    }
};

ObjectBase* PdPatchViewController::createObject(std::string text, int x, int y)
{
    if (!data.pdProcess)
        return 0;

    ObjectBase* n = UIObjectFactory::createUiObject(text); //new NodeObject;
    n->objectText = text;
    n->x = x;
    n->y = y;

    if (text.size())
        n->pdObjectID = data.canvas->createObject(text, x, y);

    //    else
    //        n->emptyBox = true;

    n->pdObject = (xpd::PdObject*)const_cast<xpd::Object*>(data.canvas->objects().findObject(n->pdObjectID));

    n->data.errorBox = (n->pdObject == 0);

    if (!n->pdObject)
        return 0;

    //    if (n->pdObject) {
    //        n->inletCount = n->pdObject->inletCount();
    //        n->outletCount = n->pdObject->outletCount();
    //
    //
    n->updateFromPdObject();

    std::string info = text + " ins: " + std::to_string(n->inletCount) + " outs:" + std::to_string(n->outletCount);
    data.pdProcess->post(info+"\n");

    n->width = 90;

    addSubview(n);

    //    data.objects.push_back(n);

    data.addObject(n);

    n->addAction(UIObject::oAutocomplete, &autocomplete);
    n->addAction(UIObject::oObjectChanged, &objectUpdated);
    n->addAction(ObjectBase::oInletClicked, &inletClicked);
    n->addAction(ObjectBase::oInletHovered, &inletHovered);
    n->addAction(ObjectBase::oOutletClicked, &outletClicked);

    n->pdObject->registerObserver(xpd::ObserverPtr(&n->observer));

    return n;
}

void PdPatchViewController::connectObjects(ObjectBase* outObj, int outIdx, ObjectBase* inObj, int inIdx)
{
    UIPatchcord* c = new UIPatchcord;
    c->outputObj = outObj;
    c->outputIdx = outIdx;
    c->inputObj = inObj;
    c->inputIdx = inIdx;

    data.canvas->connect(outObj->pdObjectID, outIdx, inObj->pdObjectID, inIdx);

    addSubview(c);
    data.addPatchcord(c);
}

void PdPatchViewController::connectObjectsByIndices(int outObjIdx, int outletIdx, int inObjIdx, int inletIdx)
{
    ObjectBase* obj1 = data.getObjectByIndex(outObjIdx);
    ObjectBase* obj2 = data.getObjectByIndex(inObjIdx);

    if (!obj1 || !obj2) {
        printf("object not found - could not connect");
        return;
    }

    // todo: correct error object connections handling
    if (outletIdx >= obj1->outletCount)
        return;
    if (inletIdx >= obj2->inletCount)
        return;

    if (!obj1->data.errorBox && !obj2->data.errorBox) {
        printf("patchcord\n");
        connectObjects(obj1, outletIdx, obj2, inletIdx);
    }
}

void PdPatchViewController::dragSelectedObjects(ImVec2 delta)
{
    if (_selectionFrame)
        return;
    for (auto o : data.objects) {
        UIObject* obj = (UIObject*)o;
        if (obj->data.selected) {
            o->x += delta.x;
            o->y += delta.y;
        }
    }
}

void PdPatchViewController::deselectAll()
{
    data.deselectObjects();
    data.deselectPatchcords();

    _multipleObjectsSelected = false;
    _draggingObjects = false;
}

void PdPatchViewController::selectSingleObject(ImVec2 pos)
{
    bool ret = false;
    for (auto o : data.objects) {
        UIObject* obj = (UIObject*)o;

        obj->data.selected = (obj->x <= pos.x);
        obj->data.selected &= (obj->y <= pos.y);
        obj->data.selected &= (obj->x + obj->width >= pos.x);
        obj->data.selected &= (obj->y + obj->height >= pos.y);

        ret |= obj->data.selected;
        _multipleObjectsSelected = false;
    }
    //        return ret;
}

bool PdPatchViewController::hitObject(ImVec2 pos)
{
    bool ret = false;
    for (auto o : data.objects) {
        UIObject* obj = (UIObject*)o;

        bool hit;
        hit = (obj->x <= pos.x);
        hit &= (obj->y <= pos.y);
        hit &= (obj->x + obj->width >= pos.x);
        hit &= (obj->y + obj->height >= pos.y);

        ret |= hit;
    }
    return ret;
}

bool PdPatchViewController::selectObjects()
{
    return data.selectObjectsInFrame(_selectionStart, _selectionEnd);
}
